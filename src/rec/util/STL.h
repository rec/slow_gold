#ifndef __REC_UTIL_STL__
#define __REC_UTIL_STL__

#include "rec/base/base.h"

namespace rec {
namespace stl {

template <typename Iterator>
void deletePointers(Iterator begin, Iterator end) {
  for (; begin != end; ++begin)
    delete *begin;
}

template <typename Container>
void deletePointers(Container* c) {
  deletePointers(c->begin(), c->end());
  c->clear();
}

template <typename Iterator>
void deleteMapPointers(Iterator begin, Iterator end) {
  for (; begin != end; ++begin)
    delete begin->second;
}

template <typename Container>
void deleteMapPointers(Container* c) {
  deleteMapPointers(c->begin(), c->end());
  c->clear();
}

template <typename Container>
typename Container::value_type pop_front(Container *c) {
  typename Container::iterator i = c->begin();
  typename Container::value_type t = *i;
  c->erase(i);
  return t;
}

// Remove the contents of from and put into to.
template <typename Container>
void moveTo(Container *from, Container *to) {
  if (to->empty()) {
    to->swap(*from);
  } else {
    to->insert(from->begin(), from->end());
    to->clear();
  }
}

}  // namespace stl
}  // namespace rec

#endif  // __REC_UTIL_STL__
