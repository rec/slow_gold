#ifndef __REC_GUI_PERSISTENTWINDOW
#define __REC_GUI_PERSISTENTWINDOW

#include "rec/data/Data.h"
#include "rec/gui/Geometry.h"

namespace rec {
namespace gui {

class PersistentWindow : public DocumentWindow {
 public:
  PersistentWindow(const String& name,
                   const Colour& bg,
                   int requiredButtons,
                   bool addToDesktop = true);
  typedef juce::Rectangle<int> Rect;

  template <typename Proto> void computeBounds();

  void setLimitedBounds(const Rect& rect);
  ~PersistentWindow();

  bool isFullScreenSize() const;

  void closeButtonPressed();

  virtual void resized();
  virtual void moved();
  void setOKToSaveLayout(bool ok = true) { okToSaveLayout_ = ok; }

 private:
  void writeData();

  data::Editable* data_;
  bool okToSaveLayout_;

  DISALLOW_COPY_AND_ASSIGN(PersistentWindow);
};

template <typename Proto>
void PersistentWindow::computeBounds() {
  data::TypedEditable<Proto>* data = data::editable<Proto>();
  data_ = data;
  DLOG(INFO) << data->get().ShortDebugString();
  setLimitedBounds(copy(data->get().bounds()));
  setFullScreen(data->get().full_screen());
}


}  // namespace gui
}  // namespace rec

#endif   // __REC_GUI_PERSISTENTWINDOW
