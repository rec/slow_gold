#ifndef __REC_GUI_PERSISTENTWINDOW
#define __REC_GUI_PERSISTENTWINDOW

#include "rec/data/Data.h"
#include "rec/data/DataListener.h"
#include "rec/gui/Geometry.h"
#include "rec/gui/GuiWriteable.h"
#include "rec/gui/WindowPosition.pb.h"

namespace rec {
namespace gui {

class PersistentWindow : public DocumentWindow,
                         public data::GlobalDataListener<WindowPosition>,
                         public GuiWriteable {
 public:
  PersistentWindow(const String& name,
                   const Colour& bg,
                   int requiredButtons,
                   bool addToDesktop = true);
  ~PersistentWindow();

  virtual void operator()(const WindowPosition&);

  bool isFullScreenSize() const;
  void closeButtonPressed();

  virtual void resized();
  virtual void moved();
  virtual void doWriteGui();

 protected:
  CriticalSection lock_;

 private:
  void writeData();

  WindowPosition position_;
  juce::Rectangle<int> resizeLimits_;
  bool needsWrite_;
  int64 lastUpdateTime_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(PersistentWindow);
};

}  // namespace gui
}  // namespace rec

#endif   // __REC_GUI_PERSISTENTWINDOW
