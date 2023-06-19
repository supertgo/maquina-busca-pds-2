#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <string>
#include <vector>

class FileUtil {
public:
  /**
   * @brief Retorna um booleano se a string termina com o sufixo
   * @param representa a string que será analisada
   * @param sufixo
   */
  bool EndsWith(const std::string &str, const std::string &suffix);

  /**
   * @brief Recebe uma string e retorna um vector de strings separando o
   * parametro em um vector de palavras
   * @param line Conjunto de palavaras digitadas pelo usuário 
   */
  std::vector<std::string> SplitIntoWords(const std::string &line);
};

#endif
