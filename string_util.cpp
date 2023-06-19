#include "string_util.h"
#include <algorithm>
#include <cctype>

std::string StringUtil::KeepAlphabeticCharacters(const std::string& input) {
    std::string output;
    for (char ch : input) {
        if (std::isalpha(ch)) {
            output += ch;
        }
    }
    return output;
}

std::string StringUtil::ToLower(const std::string& input) {
    std::string output = input;
    std::transform(output.begin(), output.end(), output.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return output;
}
