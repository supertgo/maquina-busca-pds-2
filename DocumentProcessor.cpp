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
  documentsName = result.documents;

  return result;
}

void DocumentProcessor::printDocumentHits() const {
  std::map<std::string, int> documentHits;

  for (const std::string &document : documentsName) {
    bool containsAllWords = true;

    std::cout << words_.size() << std::endl;
    for (const std::string &word : words_) {

      std::string normalized = stringUtil_.keepAlphabeticCharacters(word);
      std::string key = stringUtil_.toLower(normalized);

      if (!key.empty() && invertedIndex_.at(key).count(document) == 0) {
        containsAllWords = false;
        break;
      }
    }

    if (containsAllWords) {
      for (const std::string &word : words_) {
        std::string normalized = stringUtil_.keepAlphabeticCharacters(word);
        std::string key = stringUtil_.toLower(normalized);

        if (!key.empty()) {
          int count = invertedIndex_.at(key).at(document);
          documentHits[document] += count;
        }
      }
    }
  }

  std::vector<std::pair<std::string, int>> sortedDocuments(documentHits.begin(),
                                                           documentHits.end());
  std::sort(sortedDocuments.begin(), sortedDocuments.end(),
            [](const auto &a, const auto &b) {
              if (a.second == b.second) {
                return a.first < b.first;
              }
              return a.second > b.second;
            });

  for (const auto &doc : sortedDocuments) {
    std::cout << "Document: " << doc.first << ", Hits: " << doc.second
              << std::endl;
  }
}
