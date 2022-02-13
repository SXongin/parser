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

#include <concepts>  // std::same_as
#include <utility>   // std::move

#include "scanner.h"

namespace parser {

template<typename ScannerT>
requires requires (ScannerT s) {
  {s.GetChar()} -> std::same_as<typename ScannerT::CharT>;
  {s.Empty()} -> std::same_as<bool>;
}
class Lexer {
  public:
  explicit Lexer(ScannerT scanner) noexcept : scanner_{std::move(scanner)} {}
  explicit Lexer(std::string const& str) noexcept : scanner_{std::begin(str), std::end(str)} {}
  explicit Lexer(char const* cstr) noexcept : scanner_{cstr, '\0'} {}

 private:
  ScannerT scanner_;
};

Lexer(std::string const &) -> Lexer<Scanner<typename std::string::const_iterator, typename std::string::const_iterator>>;
Lexer(char const*) -> Lexer<Scanner<char const*, char>>;

} // namespace parser

#endif // PASER_INCLUDE_PARSER_LEXER_H
