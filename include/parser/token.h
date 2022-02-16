/**
 * @file token.h
 * @author Song Xin (SXongin@outlook.com)
 * @brief Define token class
 * @version 0.1
 * @date 2022-01-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef PARSER_INCLUDE_PARSER_TOKEN_H
#define PARSER_INCLUDE_PARSER_TOKEN_H

#include <string>   // std::string

namespace parser {

/**
 * @brief Defines TokenType
 *
 */
enum class TokenType {
  END = 0,
  NAME = 1,
  COMMA,
  LBRACK,
  RBRACK,
};

/**
 * @brief Defines Token
 *
 */
struct Token {
  TokenType type{TokenType::END};
  std::string text;
  std::strong_ordering operator<=>(Token const&) const = default;
};

std::string ToString(Token const & t);


}  // namespace parser

namespace std {
string to_string(parser::TokenType t);
string to_string(parser::Token const & t);
} // namespace std

#endif  // PARSER_INCLUDE_PARSER_TOKEN_H
