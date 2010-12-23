#ifndef __REC_UTIL_PARTITION_CONVERTORS__
#define __REC_UTIL_PARTITION_CONVERTORS__

#include <vector>

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace partition {

template <typename Str>                int getLength(const Str&);
template <typename Str>                Str toLowerCase(const Str& s);

template <typename List, typename Item> void add(List* list, Item item);
template <typename List, typename Item> Item get(const List& list, int i);

String getName(const File& f);
string getName(const string& v);

}  // namespace partition
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_PARTITION_CONVERTORS__
