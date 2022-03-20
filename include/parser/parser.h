/**
 * @file parser.h
 * @author Song Xin (SXongin@outlook.com)
 * @brief
 * @details
 * grammar NestedNameList;
 * list : '[' elements ']' ; // match bracketed list
 * elements : element (',' element)* ; // match comma-separated list
 * element : NAME | list ; // element is name or nested list
 * @version 0.1
 * @date 2022-02-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef PARSER_INCLUDE_PARSER_PARSER_H
#define PARSER_INCLUDE_PARSER_PARSER_H

// #include <array> // std::array

#include "error.h"  // parser::ParseError
#include "lexer.h"
#include "scanner.h"

namespace parser {

template <typename ScannerT>
class Parser {
 public:
  explicit Parser(Lexer<ScannerT> lexer) : lexer_{lexer} { Init(); }
  explicit Parser(std::string const& s) : lexer_{s} { Init(); }
  explicit Parser(char const* s) : lexer_{s} { Init(); }
  void list() {
    Match(TokenType::LBRACK);
    elements();
    Match(TokenType::RBRACK);
  }

  void elements() {
    element();
    while (look_ahead_.type_ == TokenType::COMMA) {
      Match(TokenType::COMMA);
      element();
    }
  }

  void element() {
    if (look_ahead_.type_ == TokenType::NAME) {
      Match(TokenType::NAME);
    } else if (look_ahead_.type_ == TokenType::LBRACK) {
      list();
    } else {
      throw ParseError{"Expected a element but meet " + std::to_string(look_ahead_)};
    }
  }

  void Match(TokenType type) {
    if (look_ahead_.type_ == type) {
      look_ahead_ = lexer_.NextToken();
    } else {
      throw ParseError{"Miss match, expected " + std::to_string(type) +
                        " but meet " + std::to_string(look_ahead_)};
    }
  }
 private:
  Lexer<ScannerT> lexer_;
//  constexpr static std::ptrdiff_t kBufSize{2};
//  std::array<Token, kBufSize> buffer_;
  Token look_ahead_;

  void Init() {
    look_ahead_ = lexer_.NextToken();
  }
};
Parser(std::string const&)
    ->Parser<Scanner<typename std::string::const_iterator,
                     typename std::string::const_iterator>>;
Parser(char const*)->Parser<Scanner<char const*, char>>;

}  // namespace parser

#endif  // PARSER_INCLUDE_PARSER_PARSER_H
