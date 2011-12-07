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
  void writeGui();

 protected:
  CriticalSection lock_;
  bool running_;

 private:
  void doSetBounds();
  void fixPosition(WindowPosition*);
  void writeData();
  bool okToSavePosition_;
  WindowPosition position_;
  juce::Rectangle<int> resizeLimits_;
  bool ignoreNextResize_;
  bool needsWrite_;
  int64 lastUpdateTime_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(PersistentWindow);
};

}  // namespace gui
}  // namespace rec

#endif   // __REC_GUI_PERSISTENTWINDOW
