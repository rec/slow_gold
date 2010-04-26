#include <gtest/gtest.h>

#include "rec/json/Parser.h"

namespace tinyjson {

using node::Node;

namespace {


class ParserTest : public testing::Test {
 public:
  ParserTest() : parser_(&tree_) {}

  virtual void SetUp() {
    tree_.clear();
  }

  void ExpectTreeEqual(Node* begin, Node* end) {
    int expectedLen = end - begin;
    int actualLen = tree_.size();

    EXPECT_EQ(expectedLen, actualLen);
    for (int i = 0; i < std::min(expectedLen, actualLen); ++i) {
      Node &x = begin[i], &y = tree_[i];
      EXPECT_TRUE(x == y)
        << "Node " << i
        << ": (" << x.type_ << ",\"" << x.begin_ << "\"," << x.length_ << ") !="
        << " (" << y.type_ << ",\"" << y.begin_ << "\"," << y.length_ << ")"
        << std::endl;
    }
  }

  void ExpectParse(Node* begin, Node* end, const char* source) {
    Parser::Error error = parser_.parse(source);
    EXPECT_TRUE(!error) << "Got error " << error;
    ExpectTreeEqual(begin, end);
  }

 protected:
  node::Tree tree_;
  Parser parser_;
};


TEST_F(ParserTest, Empty) {
  Node expected[] = {};
  ExpectParse(expected, expected, "");
}

TEST_F(ParserTest, Number) {
  const char source[] = "123";
  Node expected[] = {{node::NUMBER, source, 3}};

  ExpectParse(expected, expected + 1, source);

  const char* error = parser_.parse("123.");
  EXPECT_STREQ(error, "No digits after decimal point.");
}

TEST_F(ParserTest, String) {
  const char source[] = "\"123\"";
  Node expected[] = {{node::STRING, source, 5}};
  ExpectParse(expected, expected + 1, source);
}

TEST_F(ParserTest, True) {
  const char source[] = "true";
  Node expected[] = {{node::LITERAL, source, 4}};
  ExpectParse(expected, expected + 1, source);
}

TEST_F(ParserTest, False) {
  const char source[] = "false";
  Node expected[] = {{node::LITERAL, source, 5}};
  ExpectParse(expected, expected + 1, source);
}

TEST_F(ParserTest, Null) {
  const char source[] = "null";
  Node expected[] = {{node::LITERAL, source, 4}};
  ExpectParse(expected, expected + 1, source);
}

TEST_F(ParserTest, BadLiteral) {
  EXPECT_STREQ(parser_.parse("nulll"), "literal: wasn't true, false or null");
}


TEST_F(ParserTest, EmptyArray) {
  const char source[] = "[]";
  Node expected[] = {{node::ARRAY, source, 0}};
  ExpectParse(expected, expected + 1, source);
}

TEST_F(ParserTest, ArrayWithOneNumber) {
  static const char source[] = "[1]";
  Node expected[] = {
    {node::ARRAY, source, 1},
    {node::NUMBER, source + 1, 1},
  };

  ExpectParse(expected, expected + 2, source);
}

TEST_F(ParserTest, ArrayWithOneNumberAndComma) {
  static const char source[] = "[1,]";
  Node expected[] = {
    {node::ARRAY, source, 1},
    {node::NUMBER, source + 1, 1},
  };

  ExpectParse(expected, expected + 2, source);
}

TEST_F(ParserTest, ArrayWithSpaces) {
  static const char source[] = " [ 1 , ] ";
  Node expected[] = {
    {node::ARRAY, source + 1,  1},
    {node::NUMBER, source + 3, 2},
  };

  ExpectParse(expected, expected + arraysize(expected), source);
}

TEST_F(ParserTest, ArrayWithTwoElements) {
  static const char source[] = " [ 1 , 2] ";
  Node expected[] = {
    {node::ARRAY, source + 1,  2},
    {node::NUMBER, source + 3, 2},
    {node::NUMBER, source + 7, 1},
  };

  ExpectParse(expected, expected + arraysize(expected), source);
}

TEST_F(ParserTest, EmptyObject) {
  static const char source[] = "{}";
  Node expected[] = {
    {node::OBJECT, source,  0},
  };

  ExpectParse(expected, expected + arraysize(expected), source);
}

TEST_F(ParserTest, ObjectWithOneElement) {
  static const char source[] = "{\"a\": 1}";
  Node expected[] = {
    {node::OBJECT, source,  2},
    {node::STRING, source + 1,  3},
    {node::NUMBER, source + 6,  1},
  };

  ExpectParse(expected, expected + arraysize(expected), source);
}

TEST_F(ParserTest, ComplexObject) {
  static const char source[] = "[{\"a\": 1, \"bee\": true}, null, [{}]]";
  Node expected[] = {
    {node::ARRAY, source,  8},
    {node::OBJECT, source + 1,  4},
    {node::STRING, source + 2,  3},
    {node::NUMBER, source + 7,  1},
    {node::STRING, source + 10,  5},
    {node::LITERAL, source + 17,  4},
    {node::LITERAL, source + 24,  4},
    {node::ARRAY, source + 30,  1},
    {node::OBJECT, source + 31,  0},
  };

  ExpectParse(expected, expected + arraysize(expected), source);
}


}
}  // namespace tinyjson
