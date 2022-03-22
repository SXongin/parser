/**
 * @file lexer.h
 * @author Song Xin (SXongin@outlook.com)
 * @brief
 * @details
 * NAME : ('a'..'z'|'A'..'Z')+ ; // NAME is sequence of >=1 letter
 * @version 0.1
 * @date 2022-02-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef PASER_INCLUDE_PARSER_LEXER_H
#define PASER_INCLUDE_PARSER_LEXER_H

#include <cctype>    // std::isalpha
#include <concepts>  // std::same_as
#include <utility>   // std::move

#include "error.h"    // parser::ParseError
#include "scanner.h"  // parser::Scanner
#include "token.h"    // parser::Token

namespace parser {

template <typename ScannerT>
requires requires(ScannerT s) {
  { s.Peek() } -> std::same_as<typename ScannerT::CharT>;
  { s.Empty() } -> std::same_as<bool>;
}
class Lexer {
 public:
  explicit Lexer(ScannerT scanner) : scanner_{std::move(scanner)} {}
  explicit Lexer(std::string const& str)
      : scanner_{std::begin(str), std::end(str)} {}
  explicit Lexer(char const* cstr) : scanner_{cstr, '\0'} {}

  Token NextToken() noexcept(false) {
    while (!scanner_.Empty()) {
      CharT c = scanner_.Peek();
      switch (c) {
        case ',': {
          scanner_.Consume();
          return {TokenType::COMMA, ","};;
        }
        case '[': {
          scanner_.Consume();
          return {TokenType::LBRACK, "["};
        }
        case ']': {
          scanner_.Consume();
          return {TokenType::RBRACK, "]"};
        }
        case '=': {
          scanner_.Consume();
          return {TokenType::EQUALS, "="};
        }
        default: {
          if (std::isspace(static_cast<unsigned char>(c)) != 0) {
            scanner_.Consume();
            while (!scanner_.Empty() &&
                   std::isspace(static_cast<unsigned char>(scanner_.Peek())) !=
                       0) {
              scanner_.Consume();
            }
            continue;
          }
          if (std::isalpha(static_cast<unsigned char>(c)) != 0) {
            scanner_.Consume();
            return scan_name(c);
          }
          throw ParseError(std::string("Invalid character: ").append(1, c));
        }
      }
    }
    return {TokenType::END, ""};
  }

 private:
  ScannerT scanner_;
  using CharT = typename ScannerT::CharT;

  Token scan_name(CharT c) {
    std::string name(1, c);
    while (!scanner_.Empty()) {
      c = scanner_.Peek();
      if (std::isalpha(static_cast<unsigned char>(c)) != 0) {
        name.push_back(c);
        scanner_.Consume();
      } else {
        break;
      }
    }
    return {TokenType::NAME, std::move(name)};
  }
};

Lexer(std::string const&)
    ->Lexer<Scanner<typename std::string::const_iterator,
                    typename std::string::const_iterator>>;
Lexer(char const*)->Lexer<Scanner<char const*, char>>;

}  // namespace parser

#endif  // PASER_INCLUDE_PARSER_LEXER_H
