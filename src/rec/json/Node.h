#ifndef __TINYJASON_NODE
#define __TINYJASON_NODE

#include <ctype.h>
#include <string>
#include <vector>

#include "rec/base/StringRange.h"

namespace tinyjson {

struct Node {
  enum Type {
    NONE,
    OBJECT,
    ARRAY,
    STRING,
    NUMBER,
    LITERAL,
  };

  Type type_;

  // Pointer to the start of this node in the original character string.
  const char* begin_;

  // length_ is in Nodes for the parent types, OBJECT and ARRAY, and in bytes
  // for the child types, STRING, NUMBER and LITERAL.
  int length_;

  bool isParent() { return type_ == OBJECT || type_ == ARRAY; }
  static Type getType(char c);

  typedef std::vector<Node> Tree;

  // These next two methods assume that this Node is an entry in a Tree
  // organized as a Parser does.
  Node* getChild(int index);
  Node* getChild(const rec::util::StringRange& s);
};

bool operator==(const Node& x, const Node& y);



}  // namespace tinyjson

#endif  // __TINYJASON_NODE
