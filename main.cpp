#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#define MAX_FILE_NUMBERS 30

std::string keep_alphabetic_characters(const char *input) {
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

std::string to_lower(const std::string &input) {
  std::string output = input;
  std::transform(output.begin(), output.end(), output.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  return output;
}

std::vector<std::string> split_into_words(const std::string &line) {
  std::istringstream iss(line);
  std::vector<std::string> words;
  std::string word;

  while (iss >> word) {
    words.push_back(word);
  }

  return words;
}

void get_colleted_inverted_index(std::map<std::string, std::map<std::string, int>>& inverted_index) {
  for (int i = 1; i <= MAX_FILE_NUMBERS; i++) {
    char palavra[1000];
    FILE *file;
    std::string file_name = "./documentos/d" + std::to_string(i);
    file_name = file_name + ".txt";
    file = fopen(file_name.c_str(), "rt");

    if (file == NULL) {
      std::cout << "Não foi possivel localizar o arquivo" << std::endl;
      return;
    }

    while (fscanf(file, "%s", palavra) != EOF) {
      std::string normalized = keep_alphabetic_characters(palavra);
      std::string key = to_lower(normalized);

      if (!key.empty()) {
        inverted_index[key]["d" + std::to_string(i)]++;
      }
    }
  }
}

int main() {
  std::map<std::string, std::map<std::string, int>> inverted_index;
  get_colleted_inverted_index(inverted_index);

  std::cout << "Coloque a entrada: ";
  std::string input;
  std::getline(std::cin, input);
  std::vector<std::string> words = split_into_words(input);
  std::multimap<std::string, std::pair<std::string, int>> wordDocuments;

  for (const std::string &word : words) {
    if (inverted_index.count(word) > 0) {
      for (const auto &docCountPair : inverted_index[word]) {
        const std::string &document = docCountPair.first;
        int count = docCountPair.second;
        wordDocuments.emplace(word, std::make_pair(document, count));
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
  bool firstPair = true;
  for (const auto &wordDocPair : sortedDocuments) {
    const std::string &word = wordDocPair.first;
    const std::string &document = wordDocPair.second.first;
    int count = wordDocPair.second.second;

    if (word != currentWord) {
      if (!firstPair) {
        std::cout << std::endl;
      }
      std::cout << word << ": ";
      currentWord = word;
      firstPair = true;
    } else {
      std::cout << ", ";
    }

    std::cout << "(" << document << ".txt, " << count << ")";
    firstPair = false;
  }
  std::cout << std::endl;
  return 0;
}
