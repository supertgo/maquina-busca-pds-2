#include "FileUtil.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

bool FileUtil::endsWith(const std::string& str, const std::string& suffix) {
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

std::vector<std::string> FileUtil::splitIntoWords(const std::string& line) {
    std::istringstream iss(line);
    std::vector<std::string> words;
    std::string word;
    while (iss >> word) {
        words.push_back(word);
    }
    return words;
}

std::string FileUtil::readFileContent(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Falha ao abrir o arquivo: " << filePath << std::endl;
        return "";
    }
    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}

