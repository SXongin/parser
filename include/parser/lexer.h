/**
 * @file lexer.h
 * @author Song Xin (SXongin@outlook.com)
 * @brief
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
  explicit Lexer(ScannerT scanner) : scanner_{std::move(scanner)} { Consume(); }
  explicit Lexer(std::string const& str)
      : scanner_{std::begin(str), std::end(str)} {
    Consume();
  }
  explicit Lexer(char const* cstr) : scanner_{cstr, '\0'} { Consume(); }

  [[nodiscard]] Token Peek() const noexcept { return token_; }

  void Consume() noexcept(false) {
    while (!scanner_.Empty()) {
      CharT c = scanner_.Peek();
      switch (c) {
        case ',': {
          token_ = {TokenType::COMMA, ","};
          scanner_.Consume();
          return;
        }
        case '[': {
          token_ = {TokenType::LBRACK, "["};
          scanner_.Consume();
          return;
        }
        case ']': {
          token_ = {TokenType::RBRACK, "]"};
          scanner_.Consume();
          return;
        };
        default: {
          if (std::isspace(static_cast<unsigned char>(c)) != 0) {
            scanner_.Consume();
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
    token_ = {TokenType::END, ""};
  }

 private:
  ScannerT scanner_;
  Token token_;
  using CharT = typename ScannerT::CharT;

  void scan_name(CharT c) {
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
    token_ = {TokenType::NAME, std::move(name)};
  }
};

Lexer(std::string const&)
    ->Lexer<Scanner<typename std::string::const_iterator,
                    typename std::string::const_iterator>>;
Lexer(char const*)->Lexer<Scanner<char const*, char>>;

}  // namespace parser

#endif  // PASER_INCLUDE_PARSER_LEXER_H
