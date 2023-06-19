#include "document_processor.h"
#include <iostream>

int main() {
  std::string folder_path = "documentos";
  DocumentProcessor processor(folder_path);

  std::string input;
  std::cout << "Coloque a entrada: ";
  std::getline(std::cin, input);

  DocumentProcessor::InvertedIndexResult result =
      processor.ProcessDocuments(input);

  if (result.success) {
    processor.HandleUserInput();
  }

  return 0;
}
