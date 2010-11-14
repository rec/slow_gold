#ifndef __REC_WIDGET_TREE_CONVERTORS__
#define __REC_WIDGET_TREE_CONVERTORS__

#include <vector>

#include "rec/base/base.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace widget {
namespace tree {

template <typename Str>                int getLength(const Str&);
template <typename Str>                Str toLowerCase(const Str& s);

template <typename List, typename Item> void add(List* list, Item item);
template <typename List, typename Item> Item get(const List& list, int i);

String getName(const File& f);
string getName(const string& v);

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_CONVERTORS__
