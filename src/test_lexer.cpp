#include <gtest/gtest.h>
#include <parser/lexer.h>
#include <parser/scanner.h>
#include <iostream> // std::cout

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

TEST(Lexer, Peek) {
  {
    std::string empty;
    parser::Lexer lexer{parser::Scanner{std::begin(empty), std::end(empty)}};
    EXPECT_EQ(lexer.NextToken(), (parser::Token{parser::TokenType::END, ""}));
  }
  {
    std::string demo{"[a, ab]"};
    parser::Lexer lexer{parser::Scanner{std::begin(demo), std::end(demo)}};
    EXPECT_EQ(lexer.NextToken(), (parser::Token{parser::TokenType::LBRACK, "["}));
    EXPECT_EQ(lexer.NextToken(), (parser::Token{parser::TokenType::NAME, "a"}));
    EXPECT_EQ(lexer.NextToken(), (parser::Token{parser::TokenType::COMMA, ","}));
    EXPECT_EQ(lexer.NextToken(), (parser::Token{parser::TokenType::NAME, "ab"}));
    EXPECT_EQ(lexer.NextToken(), (parser::Token{parser::TokenType::RBRACK, "]"}));
    EXPECT_EQ(lexer.NextToken(), (parser::Token{parser::TokenType::END, ""}));
  }
}
