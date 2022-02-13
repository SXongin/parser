#include <parser/lexer.h>

#include <gtest/gtest.h>

#include <parser/scanner.h>

TEST(Lexer, Construct) {
  {
  std::string empty{};
  parser::Lexer lexer{parser::Scanner{std::begin(empty), std::end(empty)}};
  }
  {
    std::string empty{};
    parser::Lexer lexer{empty};
  }
  {
    char const* begin = "";
    parser::Lexer lexer{begin};
  }
}

