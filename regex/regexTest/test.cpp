#include <InfixConverter.h>
#include <Red.h>

#include "gtest/gtest.h"
TEST(Regex, emptyString) { ASSERT_FALSE(Red::match("", "test")); }

// TEST(Regex, characterLiteral) { ASSERT_TRUE(Red::match("a", "a")); }

TEST(InfixToPostfix, emptyString) {
  InfixConverter ic;
  ASSERT_EQ("", ic.convert(""));
}

TEST(InfixToPostfix, easyPatterns) {
  InfixConverter ic;
  EXPECT_EQ("ab.c.", ic.convert("abc"));
  EXPECT_EQ("abb.+.a.", ic.convert("a(bb)+a"));
}
