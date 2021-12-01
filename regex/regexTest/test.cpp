#include <Red.h>
#include <Compiler.h>
#include <NFASimulator.h>

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
	EXPECT_EQ("abb.+.c.", ic.convert("a(bb)+c"));
}

TEST(InfixToPostfix, harderPatterns){
	InfixConverter ic;
	EXPECT_EQ("ab+c*.a?..d+.e.", ic.convert("a(b+c*a?)d+e"));
}

TEST(RegexMatch, basicPass){
	InfixConverter ic;
	Compiler c(ic);
	const auto NFA = c.compile("abc");
	NFASimulator nfs;
	EXPECT_TRUE(nfs.match(NFA, "abc"));

}

TEST(RegexMatch, basicFail){
	InfixConverter ic;
	Compiler c(ic);
	const auto NFA = c.compile("abc");
	NFASimulator nfs;
	EXPECT_FALSE(nfs.match(NFA, "abd"));
}