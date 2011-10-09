#ifndef __REC_GUI_PERSISTENTWINDOW
#define __REC_GUI_PERSISTENTWINDOW

#include "rec/data/persist/Persist.h"
#include "rec/gui/Geometry.h"

namespace rec {
namespace gui {

class PersistentWindow : public DocumentWindow {
 public:
  PersistentWindow(const String& name,
                   const Colour& bg,
                   int requiredButtons,
                   bool addToDesktop = true)
      : DocumentWindow(name, bg, requiredButtons, addToDesktop),
        data_(NULL), okToSaveLayout_(false) {
  }
  typedef juce::Rectangle<int> Rect;

  template <typename Proto>
  void computeBounds() {
    persist::TypedEditable<Proto>* data = persist::editableGlobal<Proto>();
    data_ = data;
    setLimitedBounds(data->fileReadSuccess() ? copy(data->get().bounds()) :
                     Rect(300, 100, 800, 600));  // TODO!
    setFullScreen(data->get().full_screen());
  }
  void setLimitedBounds(const Rect& rect);
  ~PersistentWindow();

  bool isFullScreenSize() const;

  void closeButtonPressed();

  virtual void resized();
  virtual void moved();

 private:
  void writeData();

  data::Editable* data_;
  bool okToSaveLayout_;

  DISALLOW_COPY_AND_ASSIGN(PersistentWindow);
};


}  // namespace gui
}  // namespace rec

#endif   // __REC_GUI_PERSISTENTWINDOW
