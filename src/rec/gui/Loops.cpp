#include "rec/gui/Loops.h"
#include "rec/util/Defaulter.h"

namespace rec {
namespace gui {

static Defaulter<TableColumnList> dflt("\
column {\n\
  type: STRING\n\
  name: Name\n\
  address {\n\
    field {\n\
      name: name\n\
    }\n\
  }\n\
}\n\
");

Loops::Loops(const TableColumnList* desc) : LoopsBase(dflt.get(desc), 
                                            Address("segment"), Address("selected")) {}

}  // namespace gui
}  // namespace rec
