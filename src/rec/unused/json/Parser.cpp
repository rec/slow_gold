#include "rec/json/Parser.h"

namespace tinyjson {

const Parser::Error Parser::NO_ERROR = NULL;

Parser::Error Parser::parse(const StringRange& range) {
  StringRange::operator=(range);
  return item();
}

namespace {

typedef Parser::Error (Parser::*ParserHandler)();

}  // namespace


Parser::Error Parser::item() {
  skip(isspace);
  if (empty())
    return NO_ERROR;

  Node::Type type = Node::getType(top());
  if (!type)
    return "Unexpected character";

  int itemIndex = tree_->size();
  tree_->resize(itemIndex + 1);
  at(itemIndex).begin_ = begin_;
  at(itemIndex).type_ = type;

  static ParserHandler handlers[] = {
    NULL,
    &Parser::collection,
    &Parser::collection,
    &Parser::string,
    &Parser::number,
    &Parser::literal,
  };

  if (Error err = (this->*(handlers[type]))())
    return err;

  skip(isspace);
  if (at(itemIndex).isParent())
    at(itemIndex).length_ = tree_->size() - itemIndex - 1;
  else
    at(itemIndex).length_ = begin_ - at(itemIndex).begin_;

  return NULL;
}

Parser::Error Parser::collection() {
  bool isObject = (top() == '{');
  char terminator = isObject ? '}' : ']';

  if (pop() != '[' && !isObject)
    return "collection: didn't start with [ or {";

  while (!empty() && top() != terminator) {
    if (isObject) {
      if (Parser::Error err = item())
        return err;
      else if (tree_->back().type_ != Node::STRING)
        return "object: labels must be strings";
      else if (top() != ':')
        return "object: Missing colon separator";
      else
        popskip();
    }

    if (Parser::Error err = item())
      return err;
    else if (empty())
      break;

    if (top() == ',')
      popskip();
    else if (top() != terminator)
      return "array: missing comma separator";
  }
  if (empty())
    return "collection: Didn't see closing bracket.";
  pop();
  return NO_ERROR;
}

Parser::Error Parser::string() {
  if (pop() != '"')
    return "string: didn't start with \".";

  // We've just seen a " - we're just looking for the closing ".
  while (!empty()) {
    char ch = pop();
    if (ch == '"')
      return NO_ERROR;

    if (ch == '\\') {
      if (empty())
        return "string: \\ appeared in the last character";
      else
        pop();
    }
  }
  return "string: Didn't find a closing \".";
}

Parser::Error Parser::number() {
  if (top() == '-') {
    pop();
    if (empty())
      return "number: - only";
  }

  if (top() == '0')
    pop();
  else if (!isdigit(top()))
    return "number: didn't start with a digit.";
  else
    skip(isdigit);

  if (!empty() && top() == '.') {
    pop();
    if (empty() || !isdigit(top()))
      return "No digits after decimal point.";
    skip(isdigit);
  }

  if (!empty() && (top() == 'E' || top() == 'e')) {
    pop();
    if (top() == '+' || top() == '-')
      pop();
    if (!isdigit(top()))
      return "number: exponent didn't start with a digit.";
    skip(isdigit);
  }

  return NO_ERROR;
}

Parser::Error Parser::literal() {
  const char* c = begin_;
  skip(isalpha);
  int len = begin_ - c;
  if (strncmp("true", c, len) && strncmp("false", c, len) &&
      strncmp("null", c, len)) {
    return "literal: wasn't true, false or null";
  }
  return NO_ERROR;
}

}  // namespace tinyjson

