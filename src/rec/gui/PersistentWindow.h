#ifndef __REC_GUI_PERSISTENTWINDOW
#define __REC_GUI_PERSISTENTWINDOW

#include "rec/data/Data.h"
#include "rec/gui/Geometry.h"
#include "rec/gui/WindowPosition.pb.h"

namespace rec {
namespace gui {

class PersistentWindow : public DocumentWindow,
                         public Listener<const WindowPosition&> {
 public:
  PersistentWindow(const String& name,
                   const Colour& bg,
                   int requiredButtons,
                   bool addToDesktop = true);
  ~PersistentWindow();

  virtual void operator()(const WindowPosition&);
  void getPositionFromData();

  bool isFullScreenSize() const;
  void closeButtonPressed();

  virtual void resized();
  virtual void moved();
  void setOKToSavePosition(bool ok = true) { okToSavePosition_ = ok; }

 protected:
  CriticalSection lock_;

 private:
  void writeData();
  bool okToSavePosition_;
  WindowPosition position_;

  DISALLOW_COPY_AND_ASSIGN(PersistentWindow);
};

}  // namespace gui
}  // namespace rec

#endif   // __REC_GUI_PERSISTENTWINDOW
