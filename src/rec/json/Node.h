#ifndef __TINYJASON_NODE
#define __TINYJASON_NODE

#include <ctype.h>
#include <string>
#include <vector>

namespace tinyjson {
namespace node {

enum Type {
  NONE,
  OBJECT,
  ARRAY,
  STRING,
  NUMBER,
  LITERAL,
};

struct Node {
  Type type_;

  // Pointer to the start of this node in the original character string.
  const char* begin_;

  // length_ is in Nodes for the parent types, OBJECT and ARRAY, and in bytes
  // for the child types, STRING, NUMBER and LITERAL.
  int length_;

  bool isParent() { return type_ == OBJECT || type_ == ARRAY; }
};

inline Type getType(char c) {
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

inline bool operator==(const Node& x, const Node& y) {
  return x.type_ == y.type_ && x.begin_ == y.begin_ && x.length_ == y.length_;
}

template <typename Item>
Node* getChild(Node* node, Item item) {
  if (node->isParent()) {
    int childCount = 0;
    for (Node* n = node + 1; n != node + node->length_ + 1; ++childCount) {
      if (match(n, childCount, item))
        return n;
    }
  }
  return NULL;
}

typedef std::vector<Node> Tree;

}  // namespace node
}  // namespace tinyjson

#endif  // __TINYJASON_NODE
