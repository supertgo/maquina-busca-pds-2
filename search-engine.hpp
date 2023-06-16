#pragma once

#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

std::string KeepAlpha(const char *input);

std::string SetLowercase(const std::string &input);

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

std::vector<std::string> SplitWords(const std::string &line);

void GetInvertedIndex(std::map<std::string, std::map<std::string, int>>& inverted_index, int file_number);

bool ContainsAllWords(const std::vector<std::string>& words, const std::map<std::string, std::map<std::string, int>>& inverted_index, const std::string& document);