#ifndef DOCUMENT_PROCESSOR_H
#define DOCUMENT_PROCESSOR_H

#include "FileUtil.h"
#include "StringUtil.h"
#include <map>
#include <set>
#include <string>
#include <vector>

/**
 * @brief Classe responsavel pelo gerenciamento dos documentos com a entrada do
 * usuário
 */
class DocumentProcessor {
public:
  /*
   * @brief Struct que representa o retorno da função processDocuments
   * success false significa que não possível abrir o diretório
   */
  struct InvertedIndexResult {
    bool success;
    int numDocuments;
    std::set<std::string> documents;
  };

  /*
   * @brief Incializa um objeto da classe
   * @param folderPath caminho para o arquivo onde estará os documentos
   */
  DocumentProcessor(const std::string &folderPath);

  /**
   * @brief Função responsável por ler as palavras de cada um dos documentos e
   * amarzena-las no indice invertido
   * @param input Representa a string digitada pelo usuário durante a pesquisa
   */
  InvertedIndexResult processDocuments(const std::string &input);

  /**
   * @brief Função que mostra o resultado da pesquisa no terminal
   */
  void printDocumentHits(
      std::vector<std::pair<std::string, int>> sortedDocuments) const;

  /**
   * @brief Função que lida com o input do usuário
   */
  void handleUserInput();

  /**
   * @brief Função que ordena o array com os pares que contem a soma dos hits de
   * todas as palavras
   * @param sortedDocuments map sendo o primeiro elemento a palavra, o segundo
   * elemento eh um par onde o primeiro elemento é o nome do documento e o
   * segundo é a quatidade de hits Se um document tem mais que hits que o outro,
   * ele aparece primeiro, caso tenha empate, o com ordem lexicografica é
   * mostrado antes
   */
  void sortDocuments(std::vector<std::pair<std::string, int>> &sortedDocuments);

private:
  /**
   * @brief guarda o caminho de onde os documentos serão lidos
   */
  std::string folderPath_;

  /**
   * @brief Indice invetido de todas as palavras lidas apos a normalização
   * A primeira string representa a palavra, a segunda representa o nome do
   * documento e o int representa a quantidade de hits
   */
  std::map<std::string, std::map<std::string, int>> invertedIndex_;

  /**
   * @brief Vector de strings onde cada index é uma palavra que foi splitada
   * durante a pesquisa do usuário
   */
  std::vector<std::string> words_;

  /**
   * @brief Conjunto dos nomes de todos os documentos que foram lidos durante o
   * processo
   */
  std::set<std::string> documentsName_;

  StringUtil stringUtil_;
  FileUtil fileUtil_;

  void processDocument(
      const std::string &fileContent, const std::string &filename,
      const std::vector<std::string> &words,
      std::map<std::string, std::map<std::string, int>> &invertedIndex,
      std::set<std::string> &documents);
};

#endif
