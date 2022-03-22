/**
 * @file parser.h
 * @author Song Xin (SXongin@outlook.com)
 * @brief
 * @details
 * grammar NestedNameList;
 * list : '[' elements ']' ; // match bracketed list
 * elements : element (',' element)* ; // match comma-separated list
 * element : NAME '=' NAME | NAME | list ; // element is name or nested list
 * @version 0.1
 * @date 2022-02-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef PARSER_INCLUDE_PARSER_PARSER_H
#define PARSER_INCLUDE_PARSER_PARSER_H

#include <array> // std::array

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
    while (LookAhead(1).type_ == TokenType::COMMA) {
      Match(TokenType::COMMA);
      element();
    }
  }

  void element() {
    if (LookAhead(1).type_ == TokenType::NAME && LookAhead(2).type_ == TokenType::EQUALS) {
      Match(TokenType::NAME);
      Match(TokenType::EQUALS);
      Match(TokenType::NAME);
    } else if (LookAhead(1).type_ == TokenType::NAME) {
      Match(TokenType::NAME);
    } else if (LookAhead(1).type_ == TokenType::LBRACK) {
      list();
    } else {
      throw ParseError{"Expected a element but meet " +
                       std::to_string(LookAhead(1))};
    }
  }

  void Match(TokenType type) {
    if (LookAhead(1).type_ == type) {
      Consume();
    } else {
      throw ParseError{"Miss match, expected " + std::to_string(type) +
                        " but meet " + std::to_string(LookAhead(1))};
    }
  }

 private:
  Lexer<ScannerT> lexer_;
  constexpr static std::ptrdiff_t kBufSize{2};
  std::ptrdiff_t index_{0};
  std::array<Token, kBufSize> buffer_{};

  void Init() {
    for(auto & t: buffer_) {
      t = lexer_.NextToken();
    }
  }

  void Consume() noexcept {
    buffer_[index_] = lexer_.NextToken();
    index_ = (index_ + 1) % kBufSize;
  }

  Token LookAhead(ptrdiff_t ahead) const noexcept {
    return buffer_[(index_ + ahead - 1) % kBufSize];
  }
};
Parser(std::string const&)
    ->Parser<Scanner<typename std::string::const_iterator,
                     typename std::string::const_iterator>>;
Parser(char const*)->Parser<Scanner<char const*, char>>;

}  // namespace parser

#endif  // PARSER_INCLUDE_PARSER_PARSER_H
