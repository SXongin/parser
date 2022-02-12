#include <parser/token.h>

#include <gtest/gtest.h>

TEST(Parser, TokenTypeName) {
  EXPECT_EQ(std::to_string(parser::TokenType::NAME), "NAME");
  EXPECT_EQ(std::to_string(parser::TokenType::COMMA), "COMMA");
  EXPECT_EQ(std::to_string(parser::TokenType::LBRACK), "LBRACK");
  EXPECT_EQ(std::to_string(parser::TokenType::RBRACK), "RBRACK");
}

TEST(Parser, TokenName) {
  EXPECT_EQ((std::to_string(parser::Token{parser::TokenType::NAME, "demo"})), "<NAME, demo>");
}

