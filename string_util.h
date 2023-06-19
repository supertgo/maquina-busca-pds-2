#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>

class StringUtil {
public:
  /**
   * @brief Normaliza as palavras com base na norma do TP 
   * @param input Representa a string a ser normalizada 
   */
  static std::string KeepAlphabeticCharacters(const std::string &input);

  /**
   * @brief Transforma uma string na sua versão caracteres minúsculos 
   * @param input Representa a string a ser transformada 
   */
  static std::string ToLower(const std::string &input);
};

#endif // STRING_UTIL_H
