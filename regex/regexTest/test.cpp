#include <Compiler.h>
#include <NFASimulator.h>
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
  EXPECT_EQ("abb.+.c.", ic.convert("a(bb)+c"));
}

TEST(InfixToPostfix, harderPatterns) {
  InfixConverter ic;
  EXPECT_EQ("ab+c*.a?..d+.e.", ic.convert("a(b+c*a?)d+e"));
}

class RegexMatch : public ::testing::Test {
 protected:
  RegexMatch() : c(ic) {}
  InfixConverter ic;
  Compiler c;
  NFASimulator nfs;
};

TEST_F(RegexMatch, basicMatch) {
  const auto NFA = c.compile("abc");
  EXPECT_TRUE(nfs.match(NFA, "abc"));
}

TEST_F(RegexMatch, emptyNoMatch) {
  const auto NFA = c.compile("");
  EXPECT_FALSE(nfs.match(NFA, "abc"));
}

TEST_F(RegexMatch, basicNoMatch) {
  const auto NFA = c.compile("abc");
  EXPECT_FALSE(nfs.match(NFA, "abd"));
}

TEST_F(RegexMatch, longerBasicMatch) {
  const auto NFA = c.compile("findThis!");
  EXPECT_TRUE(nfs.match(NFA, "findThis!"));
}

TEST_F(RegexMatch, orNoMatch) {
  const auto NFA = c.compile("a|bc");
  EXPECT_FALSE(nfs.match(NFA, "efg"));
}

TEST_F(RegexMatch, orMatch) {
  const auto NFA = c.compile("a|bc");
  EXPECT_TRUE(nfs.match(NFA, "bc"));
}

TEST_F(RegexMatch, longerOrMatch) {
  const auto NFA = c.compile("longer|match");
  EXPECT_TRUE(nfs.match(NFA, "longer"));
}

TEST_F(RegexMatch, moreOrMatching) {
  const auto NFA = c.compile("evenlonger|stillmatching");
  EXPECT_TRUE(nfs.match(NFA, "stillmatching"));
	const auto NFA2 = c.compile("ab|ac|ad");
	EXPECT_TRUE(nfs.match(NFA2, "ad"));
	EXPECT_FALSE(nfs.match(NFA2, "ae"));
}

TEST_F(RegexMatch, longOrNoMatch){
	const auto NFA = c.compile("long or|don't match");
	EXPECT_FALSE(nfs.match(NFA, "longer o"));
	EXPECT_FALSE(nfs.match(NFA, "don't matcj"));
}