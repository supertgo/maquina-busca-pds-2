#include "DocumentProcessor.h"
#include <algorithm>
#include <dirent.h>
#include <iostream>

DocumentProcessor::DocumentProcessor(const std::string &folderPath)
    : folderPath_(folderPath) {}

DocumentProcessor::InvertedIndexResult
DocumentProcessor::processDocuments(const std::string &input) {
  InvertedIndexResult result;
  result.success = false;
  result.numDocuments = 0;

  DIR *directory;
  struct dirent *entry;
  directory = opendir(folderPath_.c_str());

  if (directory == nullptr) {
    std::cerr << "Falha ao abir o diretório" << folderPath_ << std::endl;
    return result;
  }

  while ((entry = readdir(directory)) != nullptr) {
    std::string filename = entry->d_name;
    if (fileUtil_.endsWith(filename, ".txt")) {
      std::string filePath = folderPath_ + "/" + filename;
      FILE *file = fopen(filePath.c_str(), "rt");

      if (file == NULL) {
        std::cerr << "Falha ao abrir o arquivo em: " << filePath << std::endl;
        continue;
      }

      char palavra[1000];
      while (fscanf(file, "%s", palavra) != EOF) {
        std::string normalized = stringUtil_.keepAlphabeticCharacters(palavra);
        std::string key = stringUtil_.toLower(normalized);

        if (!key.empty()) {
          invertedIndex_[key][filename]++;
        }
      }

      fclose(file);
      result.documents.insert(filename);
      result.numDocuments++;
    }
  }

  closedir(directory);
  result.success = true;
  words_ = fileUtil_.splitIntoWords(input);
  documentsName_ = result.documents;

  return result;
}

void DocumentProcessor::sortDocuments(
    std::vector<std::pair<std::string, int>> &sortedDocuments) {
  std::sort(sortedDocuments.begin(), sortedDocuments.end(),
            [](const auto &a, const auto &b) {
              if (a.second == b.second) {
                return a.first < b.first;
              }
              return a.second > b.second;
            });
}

void DocumentProcessor::printDocumentHits(
    std::vector<std::pair<std::string, int>> sortedDocuments) const {
  for (const auto &doc : sortedDocuments) {
    std::cout << "Document: " << doc.first << ", Hits: " << doc.second
              << std::endl;
  }
}

void DocumentProcessor::handleUserInput() {
  std::map<std::string, int> documentHits;

  for (const std::string &document : documentsName_) {
    bool containsAllWords = true;
    std::set<std::string> uniqueWords(words_.begin(), words_.end());

    for (const std::string &word : uniqueWords) {
      std::string normalized = stringUtil_.keepAlphabeticCharacters(word);
      std::string key = stringUtil_.toLower(normalized);

      if (key.empty() || invertedIndex_.find(key) == invertedIndex_.end() ||
          invertedIndex_.at(key).count(document) == 0) {
        containsAllWords = false;
        break;
      }
    }

    if (containsAllWords) {
      for (const std::string &word : uniqueWords) {
        std::string normalized = stringUtil_.keepAlphabeticCharacters(word);
        std::string key = stringUtil_.toLower(normalized);
        int count = invertedIndex_.at(key).at(document);
        documentHits[document] += count;
      }
    }
  }

  std::vector<std::pair<std::string, int>> sortedDocuments(documentHits.begin(),
                                                           documentHits.end());

  sortDocuments(sortedDocuments);
  printDocumentHits(sortedDocuments);
}

