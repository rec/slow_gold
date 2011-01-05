#ifndef __REC_GUI_DATADISPLAYER__
#define __REC_GUI_DATADISPLAYER__

#include "rec/gui/Layout.h"

namespace rec {
namespace gui {

template <typename Proto>
class DataDisplayer : public Layout, public Component {
 public:
  DataDisplayer() {}

  void get() {
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(DataDisplayer);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_DATADISPLAYER__
