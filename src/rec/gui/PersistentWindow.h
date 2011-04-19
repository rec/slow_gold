#ifndef __REC_SLOW_SLOWWINDOW
#define __REC_SLOW_SLOWWINDOW

#include "rec/data/persist/Persist.h"

namespace rec {
namespace gui {

class PersistentWindow : public DocumentWindow {
 public:
  PersistentWindow(const String& name,
                   const Colour& bg,
                   int requiredButtons,
                   bool addToDesktop = true)
      : DocumentWindow(name, bg, requiredButtons, addToDesktop) {
  }
  typedef juce::Rectangle<int> Rect;

  template <typename Proto>
  Rect computeBounds() {
    persist::Data<Proto>* data = persist::data<Proto>();
    setLimitedBounds(data->fileReadSuccess() ? gui::copy(data->get().bounds()) :
                     Rect(300, 100, 800, 600));  // TODO!
  }
  void setLimitedBounds(const Rect& rect);

  // TODO("SlowGold", Colours::azure, DocumentWindow::allButtons, true) {

  ~PersistentWindow();

  void closeButtonPressed();

  virtual void resized();
  virtual void moved();

 private:
  void writeData();
  void setSetter();

  persist::Setter* setter_;

  DISALLOW_COPY_AND_ASSIGN(PersistentWindow);
};

template <typename LayoutProto>


}  // namespace gui
}  // namespace rec

#endif   // __REC_SLOW_SLOWWINDOW
