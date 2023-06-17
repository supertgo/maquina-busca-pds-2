#include "DocumentProcessor.h"
#include <iostream>

int main() {
  std::string folderPath = "documentos";
  DocumentProcessor processor(folderPath);

  std::string input;
  std::cout << "Coloque a entrada: ";
  std::getline(std::cin, input);

  DocumentProcessor::InvertedIndexResult result =
      processor.processDocuments(input);

  if (result.success) {
    processor.printDocumentHits();
  }

  return 0;
}
