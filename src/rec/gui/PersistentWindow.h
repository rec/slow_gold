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

  template <typename Proto>
  void computeBounds() {
    data::TypedEditable<Proto>* data = data::editable<Proto>();
    data_ = data;
    setProtoBounds(data->get(), true);
  }

  template <typename Proto>
  void setProtoBounds(const Proto& proto, bool firstTime) {
    juce::Rectangle<int> b = copy(proto.bounds());
    if (firstTime)
      setLimitedBounds(b);
    else
      setBoundsConstrained(b);
    setFullScreen(proto.full_screen());
  }

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

}  // namespace gui
}  // namespace rec

#endif   // __REC_GUI_PERSISTENTWINDOW
