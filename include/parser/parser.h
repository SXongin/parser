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

#include "error.h"  // parser::ParseError
#include "lexer.h"
#include "scanner.h"

namespace parser {

template <typename ScannerT>
class Parser {
 public:
  explicit Parser(Lexer<ScannerT> lexer) : lexer_{lexer} {}
  explicit Parser(std::string const& s) : lexer_{s} {}
  explicit Parser(char const* s) : lexer_{s} {}
  void list() {
    Match(TokenType::LBRACK);
    elements();
    Match(TokenType::RBRACK);
  }

  void elements() {
    element();
    while (lexer_.Peek().type_ == TokenType::COMMA) {
      Match(TokenType::COMMA);
      element();
    }
  }

  void element() {
    if (lexer_.Peek().type_ == TokenType::NAME) {
      Match(TokenType::NAME);
    } else if (lexer_.Peek().type_ == TokenType::LBRACK) {
      list();
    } else {
      throw ParseError{"Expected a element but meet " + std::to_string(lexer_.Peek())};
    }
  }

  void Match(TokenType type) {
    if (lexer_.Peek().type_ == type) {
      lexer_.Consume();
    } else {
      throw ParseError{"Miss match, expected " + std::to_string(type) +
                        " but meet " + std::to_string(lexer_.Peek())};
    }
  }
 private:
  Lexer<ScannerT> lexer_;
};
Parser(std::string const&)
    ->Parser<Scanner<typename std::string::const_iterator,
                     typename std::string::const_iterator>>;
Parser(char const*)->Parser<Scanner<char const*, char>>;

}  // namespace parser

#endif  // PARSER_INCLUDE_PARSER_PARSER_H
