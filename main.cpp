#include <algorithm>
#include <cctype>
#include <dirent.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#define MAX_FILE_NUMBERS 30

struct InvertedIndexResult {
  bool success;
  int numDocuments;
  std::set<std::string> documents;
};

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

std::string keep_alphabetic_characters(const std::string &input) {
  std::string output;

  for (char ch : input) {
    if (std::isalpha(ch)) {
      output += ch;
    }
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

bool endsWith(const std::string &str, const std::string &suffix) {
  return str.size() >= suffix.size() &&
         str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

InvertedIndexResult get_colleted_inverted_index(
    std::map<std::string, std::map<std::string, int>> &inverted_index) {
  InvertedIndexResult result;
  result.success = false;
  result.numDocuments = 0;

  std::string folderPath = "documentos/";
  DIR *directory;
  struct dirent *entry;

  directory = opendir(folderPath.c_str());
  if (directory == nullptr) {
    std::cerr << "Falha ao abrir o diretório: " << folderPath << std::endl;
    return result;
  }

  while ((entry = readdir(directory)) != nullptr) {
    std::string filename = entry->d_name;
    if (endsWith(filename, ".txt")) {
      std::string filePath = folderPath + "/" + filename;
      FILE *file = fopen(filePath.c_str(), "rt");

      if (file == NULL) {
        std::cerr << "Falha ao abrir o arquivo em: " << filePath << std::endl;
        continue;
      }

      char palavra[1000];
      while (fscanf(file, "%s", palavra) != EOF) {
        std::string normalized = keep_alphabetic_characters(palavra);
        std::string key = to_lower(normalized);

        if (!key.empty()) {
          inverted_index[key][filename]++;
        }
      }

      fclose(file);
      result.documents.insert(filename);
      result.numDocuments++;
    }
  }

  closedir(directory);
  return result;
}

int main() {
  std::map<std::string, std::map<std::string, int>> inverted_index;
  InvertedIndexResult result = get_colleted_inverted_index(inverted_index);
  std::cout << "Coloque a entrada: ";
  std::string input;
  std::getline(std::cin, input);
  std::vector<std::string> words = split_into_words(input);
  std::multimap<std::string, std::pair<std::string, int>> wordDocuments;

  std::map<std::string, int> documentHits;

  for (const std::string document: result.documents) {
      bool containsAllWords = true;

      for (const std::string &word : words) {
        std::string normalized = keep_alphabetic_characters(word);
        std::string key = to_lower(normalized);

        if (!key.empty() && inverted_index[key].count(document) == 0) {
          containsAllWords = false;
          break;
        }
      }

      if (containsAllWords) {
        for (const std::string &word : words) {
          std::string normalized = keep_alphabetic_characters(word);
          std::string key = to_lower(normalized);

          if (!key.empty()) {
            int count = inverted_index[key][document];
            documentHits[document] += count;
          }
        }
      }
    }

    std::vector<std::pair<std::string, int>> sortedDocuments(
        documentHits.begin(), documentHits.end());
    std::sort(sortedDocuments.begin(), sortedDocuments.end(),
              [](const auto &a, const auto &b) {
                if (a.second == b.second) {
                  return a.first < b.first;
                }
                return a.second > b.second;
              });

    for (const auto &doc : sortedDocuments) {
      std::cout << "Documento: " << doc.first << ", Hits: " << doc.second
                << std::endl;
    }
    return 0;
  }
