#include "rec/json/Node.h"

using rec::util::StringRange;

namespace tinyjson {

Node::Type Node::getType(char c) {
  if (c == '"')
    return STRING;

  if (isdigit(c) || c == '-')
    return NUMBER;

  if (c == '[')
    return ARRAY;

  if (c == '{')
    return OBJECT;

  if (c == 'f' || c == 't' || c == 'n')
    return LITERAL;

  return NONE;
}

bool operator==(const Node& x, const Node& y) {
  return x.type_ == y.type_ && x.begin_ == y.begin_ && x.length_ == y.length_;
}

namespace {

bool match(int name, Node* begin, int index) {
  return name == index;
}

bool match(const StringRange& name, Node* begin, int index) {
  Node* n = begin + (index - 1);
  return (index % 2) && (n->type_ == Node::STRING) && !name.cmp(n->begin_ + 1);
}

template <typename Name>
Node* getChildImpl(Node* node, Name name) {
  if (node->isParent()) {
    for (Node* n = node + 1; n != node + node->length_ + 1; ++n) {
      if (match(name, node + 1, n - node - 1))
        return n;
    }
  }
  return NULL;
}

}  // namespace

Node* Node::getChild(int i)                { return getChildImpl(this, i); }
Node* Node::getChild(const StringRange& s) { return getChildImpl(this, s); }


}  // namespace tinyjson
