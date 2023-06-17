#ifndef DOCUMENT_PROCESSOR_H
#define DOCUMENT_PROCESSOR_H

#include "FileUtil.h"
#include "StringUtil.h"
#include <map>
#include <set>
#include <string>
#include <vector>

class DocumentProcessor {
public:
  struct InvertedIndexResult {
    bool success;
    int numDocuments;
    std::set<std::string> documents;
  };

  DocumentProcessor(const std::string &folderPath);

  InvertedIndexResult processDocuments(const std::string &input);
  void printDocumentHits() const;

private:
  std::string folderPath_;
  std::map<std::string, std::map<std::string, int>> invertedIndex_;
  std::vector<std::string> words_;
  std::set<std::string> documentsName;

  StringUtil stringUtil_;
  FileUtil fileUtil_;

  void processDocument(
      const std::string &fileContent, const std::string &filename,
      const std::vector<std::string> &words,
      std::map<std::string, std::map<std::string, int>> &invertedIndex,
      std::set<std::string> &documents);
};

#endif // DOCUMENT_PROCESSOR_H
