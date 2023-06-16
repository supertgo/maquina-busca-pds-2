#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "search-engine.hpp"

#define MAX_FILE_NUMBERS 30


int main() {
  std::map<std::string, std::map<std::string, int>> inverted_index;
  GetInvertedIndex(inverted_index, MAX_FILE_NUMBERS);

  std::cout << "Coloque a entrada: ";
  std::string input;
  std::getline(std::cin, input);
  std::vector<std::string> words = SplitWords(input);
  std::multimap<std::string, std::pair<std::string, int>> wordDocuments;
  std::map<std::string, std::pair<std::string, int>> filteredDocuments;

  for (const std::string &word : words) {
    if (inverted_index.count(word) > 0) {
      for (const auto &docCountPair : inverted_index[word]) {
        const std::string &document = docCountPair.first;
        int count = docCountPair.second;
        if(ContainsAllWords(words, inverted_index, document) &&
           wordDocuments.find(docCountPair.first) == wordDocuments.end()){
          wordDocuments.emplace(word, std::make_pair(document, count));
        }
      }
    }
  }

  std::vector<std::pair<std::string, std::pair<std::string, int>>>
      sortedDocuments(wordDocuments.begin(), wordDocuments.end());
  std::sort(sortedDocuments.begin(), sortedDocuments.end(),
            [](const auto &lhs, const auto &rhs) {
              return lhs.second.second > rhs.second.second;
            });

  std::cout << "Resultado:" << std::endl;

  std::string currentWord;
  std::map<std::string, int> ranking;
  bool firstPair = true;
  for (const auto &wordDocPair : sortedDocuments) {
    const std::string &word = wordDocPair.first;
    const std::string &document = wordDocPair.second.first;
    int count = wordDocPair.second.second;

    if (ranking.find(document) != ranking.end()) {
      ranking[document] += count;
    } else {
      ranking[document] = count;
    }
  }

  /*for (const auto &entry : ranking) {
  std::cout << entry.first << ": " << entry.second << std::endl;
  }*/
  for (auto it = ranking.rbegin(); it != ranking.rend(); it++) {
    std::cout << it->first << ": " << it->second << std::endl;
  }

  std::cout << std::endl;
  return 0;
}

