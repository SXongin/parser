/**
 * @file scanner.h
 * @author Song Xin (SXongin@outlook.com)
 * @brief
 * @version 0.1
 * @date 2022-02-02
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef PASER_INCLUDE_PARSER_SCANNER_H
#define PASER_INCLUDE_PARSER_SCANNER_H

#include <iterator> // std::advance std::incrementable
#include <concepts> // std::equality_comparable_with
#include <iostream>

namespace parser {

template<typename BeginT, typename EndT>
concept InterVal = requires(BeginT b_itr, EndT e_itr) {
    requires std::incrementable<BeginT>;
    requires std::equality_comparable_with<BeginT, EndT> ||
             std::equality_comparable_with<typename std::iterator_traits<BeginT>::value_type, EndT>;
};

template <typename BeginT, typename EndT>
requires InterVal<BeginT, EndT>
class Scanner {
 public:
  using CharT = typename std::iterator_traits<BeginT>::value_type;
  Scanner(BeginT b_itr, EndT e_itr) noexcept : b_itr_{b_itr}, e_itr_{e_itr}{}
  [[nodiscard]] bool Empty() const noexcept {
    if constexpr (std::equality_comparable_with<BeginT, EndT>) {
      return b_itr_ == e_itr_;
    } else { // std::equality_comparable_with<CharT, EndT>
      return *b_itr_ == e_itr_;
    }
  }
  [[nodiscard]] CharT Peek() const noexcept {
    return *b_itr_;
  }
  void Consume() noexcept {
    ++b_itr_;
  }
 private:
  BeginT b_itr_;
  EndT e_itr_;
};

} // namespace parser

#endif // PASER_INCLUDE_PARSER_SCANNER_H
