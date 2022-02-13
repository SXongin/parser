#include <parser/scanner.h>

#include <gtest/gtest.h>
#include <string> // std::string

TEST(ScannerCString, Empty) {
  {
    char const* begin = "";
    parser::Scanner scanner(begin, begin);
    EXPECT_TRUE(scanner.Empty());
  }
  {
    char const* begin = "";
    parser::Scanner scanner(begin, '\0');
    EXPECT_TRUE(scanner.Empty());
  }
}

TEST(ScannerStdString, Empty) {
  {
    std::string demo{};
    parser::Scanner scanner(std::begin(demo), std::end(demo));
    EXPECT_TRUE(scanner.Empty());
  }
}

TEST(ScannerCString, GetChar) {
  {
    char const* begin = "d";
    parser::Scanner scanner(begin, begin + 1); //NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    EXPECT_FALSE(scanner.Empty());
    EXPECT_EQ(scanner.GetChar(), 'd');
    EXPECT_TRUE(scanner.Empty());
  }
  {
    char const* begin = "d";
    parser::Scanner scanner(begin, '\0');
    EXPECT_FALSE(scanner.Empty());
    EXPECT_EQ(scanner.GetChar(), 'd');
    EXPECT_TRUE(scanner.Empty());
  }
  {
    char const* begin = "demo";
    parser::Scanner scanner(begin, '\0');
    EXPECT_FALSE(scanner.Empty());
    EXPECT_EQ(scanner.GetChar(), 'd');
    EXPECT_EQ(scanner.GetChar(), 'e');
    EXPECT_EQ(scanner.GetChar(), 'm');
    EXPECT_EQ(scanner.GetChar(), 'o');
    EXPECT_TRUE(scanner.Empty());
  }
}

TEST(ScannerStdString, GetChar) {
  {
    std::string demo = "d";
    parser::Scanner scanner(std::begin(demo), std::end(demo));
    EXPECT_FALSE(scanner.Empty());
    EXPECT_EQ(scanner.GetChar(), 'd');
    EXPECT_TRUE(scanner.Empty());
  }
  {
    std::string demo = "demo";
    parser::Scanner scanner(std::begin(demo), std::end(demo));
    EXPECT_FALSE(scanner.Empty());
    EXPECT_EQ(scanner.GetChar(), 'd');
    EXPECT_EQ(scanner.GetChar(), 'e');
    EXPECT_EQ(scanner.GetChar(), 'm');
    EXPECT_EQ(scanner.GetChar(), 'o');
    EXPECT_TRUE(scanner.Empty());
  }
}

