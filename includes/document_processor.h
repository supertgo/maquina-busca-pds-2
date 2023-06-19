#ifndef DOCUMENT_PROCESSOR_H
#define DOCUMENT_PROCESSOR_H

#include "file_util.h"
#include "string_util.h"
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
   * @brief Struct que representa o retorno da função ProcessDocuments
   * success false significa que não possível abrir o diretório
   */
  struct InvertedIndexResult {
    bool success;
    int num_documents;
    std::set<std::string> documents;
  };

  /*
   * @brief Incializa um objeto da classe
   * @param folder_path caminho para o arquivo onde estará os documentos
   */
  DocumentProcessor(const std::string &folder_path);

  /**
   * @brief Função responsável por ler as palavras de cada um dos documentos e
   * amarzena-las no indice invertido
   * @param input Representa a string digitada pelo usuário durante a pesquisa
   */
  InvertedIndexResult ProcessDocuments(const std::string &input);

  /**
   * @brief Função que mostra o resultado da pesquisa no terminal
   */
  void PrintDocumentOccurrences(
      std::vector<std::pair<std::string, int>> sorted_documents) const;

  /**
   * @brief Função que lida com o input do usuário
   */
  void HandleUserInput();

  /**
   * @brief Função que ordena o array com os pares que contem a soma dos hits de
   * todas as palavras
   * @param sorted_documents map sendo o primeiro elemento a palavra, o segundo
   * elemento eh um par onde o primeiro elemento é o nome do documento e o
   * segundo é a quatidade de hits Se um document tem mais que hits que o outro,
   * ele aparece primeiro, caso tenha empate, o com ordem lexicografica é
   * mostrado antes
   */
  void SortDocuments(std::vector<std::pair<std::string, int>> &sorted_documents);

private:
  /**
   * @brief guarda o caminho de onde os documentos serão lidos
   */
  std::string folder_path_;

  /**
   * @brief Indice invetido de todas as palavras lidas apos a normalização
   * A primeira string representa a palavra, a segunda representa o nome do
   * documento e o int representa a quantidade de hits
   */
  std::map<std::string, std::map<std::string, int>> inverted_index_;

  /**
   * @brief Vector de strings onde cada index é uma palavra que foi Splitada
   * durante a pesquisa do usuário
   */
  std::vector<std::string> words_;

  /**
   * @brief Conjunto dos nomes de todos os documentos que foram lidos durante o
   * processo
   */
  std::set<std::string> documents_name_;

  StringUtil string_util_;
  FileUtil file_util_;

  void ProcessDocument(
      const std::string &file_content, const std::string &file_name,
      const std::vector<std::string> &words,
      std::map<std::string, std::map<std::string, int>> &inverted_index,
      std::set<std::string> &documents);
};

#endif
