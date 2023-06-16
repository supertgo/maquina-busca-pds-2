#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "search-engine.hpp"

std::string KeepAlpha(const char *input) {
  std::string output;
  const char *iterator = input;

  while (*iterator) {
    if (std::isalpha(*iterator)) {
      output += *iterator;
    }
    ++iterator;
  }
  return output;
}

std::string SetLowercase(const std::string &input) {
  std::string output = input;
  std::transform(output.begin(), output.end(), output.begin(),
                 [](unsigned char c) {
                     return std::tolower(c); 
                   }
                );
                
  return output;
}

/*
  std::string Normalize(const char *input){
  std::string output;
  const char *iterator = input;

  while (*iterator) {
    if (std::isalpha(*iterator)) {
      output += *iterator;
    }
    ++iterator;
  }
  std::transform(output.begin(), output.end(), output.begin(),
                 [](unsigned char c) {
                     return std::tolower(c); 
                   }
                );
                
  return output;
}
*/

std::vector<std::string> SplitWords(const std::string &line) {
  std::istringstream iss(line);
  std::vector<std::string> words;
  std::string word;

  while (iss >> word) {
    words.push_back(word);
  }

  return words;
}

void GetInvertedIndex(std::map<std::string, std::map<std::string, int>>& inverted_index, int file_number) {
  for (int i = 1; i <= file_number; i++) {
    char str[1000];
    FILE *file;
    std::string file_name = "./documentos/d" + std::to_string(i);
    file_name = file_name + ".txt";
    file = fopen(file_name.c_str(), "rt");

    if (file == NULL) {
      std::cout << "Não foi possivel localizar o arquivo" << std::endl;
      return;
    }

    while (fscanf(file, "%s", str) != EOF) {
      std::string normalized = KeepAlpha(str);
      std::string key = SetLowercase(normalized);

      if (!key.empty()) {
        inverted_index[key]["d" + std::to_string(i)]++;
      }
    }
  }
}

bool ContainsAllWords(const std::vector<std::string>& words, const std::map<std::string, std::map<std::string, int>>& inverted_index, const std::string& document) {
  for (const std::string& word : words) {
    if (inverted_index.count(word) == 0 || inverted_index.at(word).count(document) == 0) {
      return false;
    }
  }
  return true;
}