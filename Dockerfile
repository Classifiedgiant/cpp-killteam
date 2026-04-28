# Stage 1: install vcpkg dependencies
# Kept separate so this slow layer is only rebuilt when vcpkg.json changes.
FROM debian:bookworm-slim AS deps

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    build-essential \
    ninja-build \
    git \
    curl \
    zip \
    unzip \
    tar \
    pkg-config \
    python3 \
    libssl-dev \
    uuid-dev \
    zlib1g-dev \
    libsystemd-dev \
  && rm -rf /var/lib/apt/lists/*

# Install CMake 3.31 from official cmake.org (bookworm ships 3.25, too old)
RUN curl -fsSL https://cmake.org/files/v3.31/cmake-3.31.0-linux-x86_64.sh \
      -o /tmp/cmake-install.sh \
  && sh /tmp/cmake-install.sh --prefix=/usr/local --skip-license \
  && rm /tmp/cmake-install.sh

ENV VCPKG_ROOT=/opt/vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git $VCPKG_ROOT \
    && git -C $VCPKG_ROOT checkout 2024.11.16 \
    && $VCPKG_ROOT/bootstrap-vcpkg.sh -disableMetrics

WORKDIR /src
COPY vcpkg.json .
RUN $VCPKG_ROOT/vcpkg install --triplet x64-linux


# Stage 2: compile the application
FROM deps AS build

COPY . .
RUN cmake -S . --preset Release \
  && cmake --build build --parallel


# Stage 3: run tests (build fails here if any test fails)
FROM build AS test

RUN ctest --test-dir build --output-on-failure


# Stage 4: minimal runtime image
FROM debian:bookworm-slim AS runtime

RUN apt-get update && apt-get install -y --no-install-recommends \
    libssl3 \
    libuuid1 \
    zlib1g \
  && rm -rf /var/lib/apt/lists/*

COPY --from=build /src/build/src/cppKillteam /app/cppKillteam

EXPOSE 1337
CMD ["/app/cppKillteam"]
