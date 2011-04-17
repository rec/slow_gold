#ifndef __REC_SLOW_SLOWWINDOW
#define __REC_SLOW_SLOWWINDOW

#include "rec/data/persist/Persist.h"

namespace rec {
namespace gui {

class AppLayout;

class PersistentWindow : public DocumentWindow {
 public:
  PersistentWindow();
  ~PersistentWindow();

  void closeButtonPressed();

  virtual void resized();
  virtual void moved();

 private:
  void writeData();

  DISALLOW_COPY_AND_ASSIGN(PersistentWindow);
};

}  // namespace gui
}  // namespace rec

#endif   // __REC_SLOW_SLOWWINDOW
