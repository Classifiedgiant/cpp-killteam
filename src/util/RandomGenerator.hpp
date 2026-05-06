#ifndef KILLTEAM_SRC_UTIL_RANDOMGENERATOR_H
#define KILLTEAM_SRC_UTIL_RANDOMGENERATOR_H

#include <algorithm>
#include <random>
#include <string>

namespace Util
{

static std::string GenerateAlphaNumericString(size_t length)
{
    const std::string chars = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_int_distribution<std::string::size_type> distribution(0, chars.size()-1);

    std::string alphaNumString(length, '0');

    for (auto& ch : alphaNumString)
        ch = chars[distribution(rd)];

    return alphaNumString;
}

}

#endif
