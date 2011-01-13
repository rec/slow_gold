#include "rec/gui/Loops.h"
#include "rec/util/Defaulter.h"

namespace rec {
namespace gui {

static Defaulter<TableColumnList> dflt(
"column { type: TIME name: \"Time\" address { field { name: \"time\" } } } "
"column { type: STRING name: \"Name\" address { field { name: \"name\" } } } "
"column { type: STRING name: \"Notes\" address { field { name: \"notes\" } } } "
);

Loops::Loops(const TableColumnList* desc)
  : LoopsBase(dflt.get(desc), Address("loop_point"), Address("selected")) {
  fillHeader(&getHeader());
}

}  // namespace gui
}  // namespace rec
