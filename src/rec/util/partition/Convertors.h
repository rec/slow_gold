#ifndef __REC_UTIL_PARTITION_CONVERTORS__
#define __REC_UTIL_PARTITION_CONVERTORS__

#include <vector>

#include "rec/util/Range.h"

namespace rec {
namespace util {

template <typename Str> int getLength(const Str&);
template <typename Str> Str toLowerCase(const Str& s);

template <typename List, typename Item> void add(List* list, Item item);
template <typename List, typename Item> Item get(const List& list, int i);

String getName(const File& f);
String getName(const string& v);

template <typename Collection>
String getName(const Collection& v, int i) { return getName(v[i]); }

template <typename List>
void addRangeToList(const Range<int>& range, List* list) {
  for (int i = range.begin_; i != range.end_; ++i)
    add(list, i);
}

template <typename List>
List rangeToList(const Range<int>& range) {
  List list;
  addRangeToList(range, &list);
  return list;
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_PARTITION_CONVERTORS__
