#ifndef __REC_GUI_GUIWRITEABLE__
#define __REC_GUI_GUIWRITEABLE__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class GuiWriteable {
 public:
  GuiWriteable() : needsUpdate_(false) { add(this); }
  virtual ~GuiWriteable() {}

  static void writeAll();

  static const int MIN_UPDATE_GAP = 500;

 protected:
  virtual void doWriteGui() = 0;
  void requestWrite();

  CriticalSection lock_;

 private:
  static void add(GuiWriteable*);
  void writeGui();

  bool needsUpdate_;
  int64 lastUpdateTime_;
};


}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_GUIWRITEABLE__
