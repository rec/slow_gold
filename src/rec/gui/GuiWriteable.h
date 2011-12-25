#ifndef __REC_GUI_GUIWRITEABLE__
#define __REC_GUI_GUIWRITEABLE__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class GuiWriteable {
 public:
  GuiWriteable() : needsUpdate_(false), writeable_(false) { add(this); }
  virtual ~GuiWriteable() {}

  static void writeAll();
  static void setWriteableAll(bool enable);

  static const int MIN_UPDATE_GAP = 200;

 protected:
  virtual void doWriteGui() = 0;
  void requestWrite();
  void setWriteable(bool writeable);
  bool isWriteable() const { Lock l(lock_); return writeable_; }

  CriticalSection lock_;

 private:
  static void add(GuiWriteable*);
  void writeGui();

  bool needsUpdate_;
  int64 lastUpdateTime_;
  bool writeable_;
};


}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_GUIWRITEABLE__
