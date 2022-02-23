#include <parser/parser.h>

#include <gtest/gtest.h>

TEST(Parser, Construct) {
  {
    parser::Lexer l{""};
    parser::Parser p{l};
  }
  {
    parser::Parser p{""};
  }
}

TEST(Parser, Match) {
  {
    parser::Parser p{""};
    EXPECT_NO_THROW(p.Match(parser::TokenType::END));
  }
  {
    parser::Parser p{"["};
    EXPECT_NO_THROW(p.Match(parser::TokenType::LBRACK));
  }
  {
    parser::Parser p{"]"};
    EXPECT_NO_THROW(p.Match(parser::TokenType::RBRACK));
  }
  {
    parser::Parser p{","};
    EXPECT_NO_THROW(p.Match(parser::TokenType::COMMA));
  }
  {
    parser::Parser p{"abcxyzZA"};
    EXPECT_NO_THROW(p.Match(parser::TokenType::NAME));
  }
  {
    parser::Parser p{"a"};
    EXPECT_THROW(p.Match(parser::TokenType::END), parser::ParseError);
  }
  {
    parser::Parser p{"["};
    EXPECT_THROW(p.Match(parser::TokenType::RBRACK), parser::ParseError);
  }
  {
    parser::Parser p{"]"};
    EXPECT_NO_THROW(p.Match(parser::TokenType::RBRACK));
  }
  {
    parser::Parser p{","};
    EXPECT_THROW(p.Match(parser::TokenType::NAME), parser::ParseError);
  }
  {
    parser::Parser p{""};
    EXPECT_THROW(p.Match(parser::TokenType::NAME), parser::ParseError);
  }
}

TEST(Parser, Element) {
  {
    parser::Parser p{"aaa"};
    EXPECT_NO_THROW(p.element());
  }
  {
    parser::Parser p{"[a, b]"};
    EXPECT_NO_THROW(p.element());
  }
  {
    parser::Parser p{""};
    EXPECT_THROW(p.element(), parser::ParseError);
  }
  {
    parser::Parser p{","};
    EXPECT_THROW(p.element(), parser::ParseError);
  }
}

TEST(Parser, Elements) {
  {
    parser::Parser p{"aaa"};
    EXPECT_NO_THROW(p.elements());
  }
  {
    parser::Parser p{"a, b"};
    EXPECT_NO_THROW(p.elements());
  }
  {
    parser::Parser p{""};
    EXPECT_THROW(p.elements(), parser::ParseError);
  }
  {
    parser::Parser p{"[,]"};
    EXPECT_THROW(p.element(), parser::ParseError);
  }
}

TEST(Parser, List) {
  {
    parser::Parser p{"[aaa]"};
    EXPECT_NO_THROW(p.list());
  }
  {
    parser::Parser p{"[a, b]"};
    EXPECT_NO_THROW(p.list());
  }
  {
    parser::Parser p{""};
    EXPECT_THROW(p.list(), parser::ParseError);
  }
  {
    parser::Parser p{"a"};
    EXPECT_THROW(p.list(), parser::ParseError);
  }
}
