#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <string>
#include <vector>

class FileUtil {
public:
    bool endsWith(const std::string& str, const std::string& suffix);
    std::vector<std::string> splitIntoWords(const std::string& line);
    std::string readFileContent(const std::string& filePath);
};

#endif  // FILE_UTIL_H
