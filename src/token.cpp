/**
 * @file token.cpp
 * @author Song Xin (SXongin@outlook.com)
 * @brief
 * @version 0.1
 * @date 2022-02-13
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <parser/token.h>

namespace std {

string to_string(parser::TokenType t) {
  switch (t) {
    case parser::TokenType::END:
      return "END";
    case parser::TokenType::NAME:
      return "NAME";
    case parser::TokenType::COMMA:
      return "COMMA";
    case parser::TokenType::LBRACK:
      return "LBRACK";
    case parser::TokenType::RBRACK:
      return "RBRACK";
    default:
      return {};
  }
}

string to_string(parser::Token const& t) {
  return "<" + to_string(t.type) +  ", " + t.text + ">";
}


} // namespace std
