/**
 * @file error.h
 * @author Song Xin (SXongin@outlook.com)
 * @brief
 * @version 0.1
 * @date 2022-02-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef PASER_INCLUDE_PARSER_ERROR_H
#define PASER_INCLUDE_PARSER_ERROR_H

#include <stdexcept> // std::runtime_error

namespace parser {

class ParseError : public std::runtime_error {
 public:
  using std::runtime_error::runtime_error;
};

} // namespace parser

#endif // PASER_INCLUDE_PARSER_ERROR_H
