#ifndef __REC_GUI_LAYOUT_LAYOUT__
#define __REC_GUI_LAYOUT_LAYOUT__

#include "rec/gui/Geometry.h"
#include "rec/gui/SizeHintAccumulator.h"

namespace rec {
namespace gui {

class Layout : public Component,
               public SizeHintAccumulator,
               public SettableTooltipClient {
 public:
  static const int DEFAULT_MIN = 12;
  static const int DEFAULT_MAX = -1;
  static const int DEFAULT_PREF = -1;

  Layout(const String& name = String::empty,
         Orientation o = HORIZONTAL,
         bool resizeOther = true,
         bool isMain = false);

  void setOrientation(Orientation o) { orientation_ = o; }
  Orientation orientation() const { return orientation_; }

  void addToLayout(Component* c);
  void addToLayout(Component* c, double m) { addToLayout(c, m, m, m); }
  void addToLayout(Component* c, double min, double max, double pref);

  int size() const { return components_.size(); }

  virtual void resized();
  StretchableLayoutManager* layoutManager() { return &layoutManager_; }
  virtual void layout();
  void clear(bool free = false);

  #if JUCE_WINDOWS
  virtual void paintOverChildren(Graphics& g) {
    if (isMain_) {
      g.setColour(juce::Colours::black);
      g.drawLine(0.0f, 0.0f, static_cast<float>(getWidth()), 0);
    }
  }
#endif

 protected:
  StretchableLayoutManager layoutManager_;
  vector <Component*> components_;
  Orientation orientation_;
  const bool resizeOtherDimension_;
  SizeAccumulator sizeHints_[LAST];
  juce::CachedComponentImage *cache_;
  bool const isMain_;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(Layout);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_LAYOUT_LAYOUT__
