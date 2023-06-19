#include "../../includes/document_processor.h"
#include <algorithm>
#include <dirent.h>
#include <iostream>

DocumentProcessor::DocumentProcessor(const std::string &folder_path)
    : folder_path_(folder_path) {}

DocumentProcessor::InvertedIndexResult
DocumentProcessor::ProcessDocuments(const std::string &input) {
  InvertedIndexResult result;
  result.success = false;
  result.num_documents = 0;

  DIR *directory;
  struct dirent *entry;
  directory = opendir(folder_path_.c_str());

  if (directory == nullptr) {
    std::cerr << "Falha ao abir o diretório" << folder_path_ << std::endl;
    return result;
  }

  while ((entry = readdir(directory)) != nullptr) {
    std::string file_name = entry->d_name;
    if (file_util_.EndsWith(file_name, ".txt")) {
      std::string file_path = folder_path_ + "/" + file_name;
      FILE *file = fopen(file_path.c_str(), "rt");

      if (file == NULL) {
        std::cerr << "Falha ao abrir o arquivo em: " << file_path << std::endl;
        continue;
      }

      char palavra[1000];
      while (fscanf(file, "%s", palavra) != EOF) {
        std::string normalized = string_util_.KeepAlphabeticCharacters(palavra);
        std::string key = string_util_.ToLower(normalized);

        if (!key.empty()) {
          inverted_index_[key][file_name]++;
        }
      }

      fclose(file);
      result.documents.insert(file_name);
      result.num_documents++;
    }
  }

  closedir(directory);
  result.success = true;
  words_ = file_util_.SplitIntoWords(input);
  documents_name_ = result.documents;

  return result;
}

void DocumentProcessor::SortDocuments(
    std::vector<std::pair<std::string, int>> &sorted_documents) {
  std::sort(sorted_documents.begin(), sorted_documents.end(),
            [](const auto &a, const auto &b) {
              if (a.second == b.second) {
                return a.first < b.first;
              }
              return a.second > b.second;
            });
}

void DocumentProcessor::PrintDocumentOccurrences(
    std::vector<std::pair<std::string, int>> sorted_documents) const {
  for (const auto &doc : sorted_documents) {
    std::cout << "Document: " << doc.first /*<< ", Occurrences: " << doc.second
              */<< std::endl;
  }
}

void DocumentProcessor::HandleUserInput() {
  std::map<std::string, int> document_occurrences;

  for (const std::string &document : documents_name_) {
    bool contains_all_words = true;
    std::set<std::string> unique_words(words_.begin(), words_.end());

    for (const std::string &word : unique_words) {
      std::string normalized = string_util_.KeepAlphabeticCharacters(word);
      std::string key = string_util_.ToLower(normalized);

      if (key.empty() || inverted_index_.find(key) == inverted_index_.end() ||
          inverted_index_.at(key).count(document) == 0) {
        contains_all_words = false;
        break;
      }
    }

    if (contains_all_words) {
      for (const std::string &word : unique_words) {
        std::string normalized = string_util_.KeepAlphabeticCharacters(word);
        std::string key = string_util_.ToLower(normalized);
        int count = inverted_index_.at(key).at(document);
        document_occurrences[document] += count;
      }
    }
  }

  std::vector<std::pair<std::string, int>> sorted_documents(document_occurrences.begin(),
                                                           document_occurrences.end());

  SortDocuments(sorted_documents);
  PrintDocumentOccurrences(sorted_documents);
}

