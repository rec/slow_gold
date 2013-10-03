#ifndef __REC_GUI_LAYOUT_LAYOUT__
#define __REC_GUI_LAYOUT_LAYOUT__

#include "rec/util/Disableable.h"
#include "rec/gui/Geometry.h"
#include "rec/gui/Orientation.h"
#include "rec/gui/SizeHintAccumulator.h"

namespace rec {
namespace gui {

class Constants;
class Size;

class Panel : public Component,
              public Disableable,
              public SizeHintAccumulator,
              public SettableTooltipClient {
 public:
  static const int DEFAULT_MIN = 12;
  static const int DEFAULT_MAX = -1;
  static const int DEFAULT_PREF = -1;

  Panel(const String& name = String::empty,
        Orientation o = HORIZONTAL,
        bool resizeOther = true,
        bool isMain = false,
        bool isOpaque = false);

  ~Panel();

  void setOrientation(Orientation o) { orientation_ = o; }
  Orientation orientation() const { return orientation_; }

  void addToPanel(Component* c);
  void addToPanel(Component* c, double m) { addToPanel(c, m, m, m); }
  virtual void addToPanel(Component* c, double min, double max, double pref);
  void addToPanel(Component*, const Constants&, const Size&);

  int size() const { return components_.size(); }

  virtual void resized();
  StretchableLayoutManager* layoutManager() { return &layoutManager_; }
  virtual void layout();

  void clear(bool free = false);

  void setEnabled(bool e) {
    Component::setEnabled(e);
    DLOG(INFO) << "Enable " << e << ", " << getName();
  }

  virtual bool isOpaque() const { return isOpaque_; }

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
  vector<Component*> components_;
  Orientation orientation_;
  const bool resizeOtherDimension_;
  SizeAccumulator sizeHints_[LAST];
  juce::CachedComponentImage *cache_;
  bool const isMain_;
  bool const isOpaque_;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(Panel);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_LAYOUT_LAYOUT__
