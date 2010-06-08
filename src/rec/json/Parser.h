#ifndef __TINY_JASON
#define __TINY_JASON

#include <ctype.h>
#include <vector>
#include "rec/base/StringRange.h"
#include "rec/base/disallow.h"
#include "rec/json/Node.h"

namespace tinyjson {

typedef rec::util::StringRange StringRange;

class Parser : public StringRange {
 public:
  Parser(Node::Tree* tree) : tree_(tree) {}

  typedef const char* Error;

  static const Error NO_ERROR;

  Error parse(const StringRange& range);

 private:
  void popskip() { pop(); skip(isspace); }

  Error item();
  Error collection();
  Error string();
  Error number();
  Error literal();

  Node::Tree* tree_;
  Node& at(int index) { return (*tree_)[index]; }

  DISALLOW_COPY_AND_ASSIGN(Parser);
};

}  // namespace tinyjson

#endif  // __TINY_JASON
