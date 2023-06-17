#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>

class StringUtil {
public:
   static std::string keepAlphabeticCharacters(const std::string& input);
   static std::string toLower(const std::string& input);
};

#endif  // STRING_UTIL_H
