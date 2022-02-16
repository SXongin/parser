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
    EXPECT_EQ(lexer.Peek(), (parser::Token{parser::TokenType::END, ""}));
    std::cout << std::to_string(lexer.Peek()) << std::endl;
  }
  {
    std::string demo{"[a, ab]"};
    parser::Lexer lexer{parser::Scanner{std::begin(demo), std::end(demo)}};
    EXPECT_EQ(lexer.Peek(), (parser::Token{parser::TokenType::LBRACK, "["}));
    std::cout << std::to_string(lexer.Peek()) << std::endl;
    lexer.Consume();
    EXPECT_EQ(lexer.Peek(), (parser::Token{parser::TokenType::NAME, "a"}));
    std::cout << std::to_string(lexer.Peek()) << std::endl;
    lexer.Consume();
    EXPECT_EQ(lexer.Peek(), (parser::Token{parser::TokenType::COMMA, ","}));
    std::cout << std::to_string(lexer.Peek()) << std::endl;
    lexer.Consume();
    EXPECT_EQ(lexer.Peek(), (parser::Token{parser::TokenType::NAME, "ab"}));
    std::cout << std::to_string(lexer.Peek()) << std::endl;
    lexer.Consume();
    EXPECT_EQ(lexer.Peek(), (parser::Token{parser::TokenType::RBRACK, "]"}));
    std::cout << std::to_string(lexer.Peek()) << std::endl;
    lexer.Consume();
    EXPECT_EQ(lexer.Peek(), (parser::Token{parser::TokenType::END, ""}));
    std::cout << std::to_string(lexer.Peek()) << std::endl;
  }
}
