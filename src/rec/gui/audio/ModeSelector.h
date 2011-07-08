#ifndef __REC_GUI_AUDIO_MODESELECTOR__
#define __REC_GUI_AUDIO_MODESELECTOR__

#include <map>

#include "rec/gui/layout/Layout.h"
#include "rec/util/listener/DataListener.h"
#include "rec/util/Mode.pb.h"

namespace rec {
namespace gui {
namespace audio {

class ModeSelector : public Layout, public juce::Button::Listener,
                     public DataListener<Mode> {
 public:
  ModeSelector();
  virtual ~ModeSelector() {}

  virtual void buttonClicked(juce::Button* button);
  virtual bool isOpaque() const { return true; }

  virtual void operator()(const Mode&);
  DrawableButton* getButton(const Mode::Action&);

 private:
  template <typename T>
  void setImage(DrawableButton* b, Mode::Action action) {
    b->setImages(ptr<Drawable>(T::create()).get());
  	b->addListener(this);
  	addToLayout(b);
  	buttons_[action] = b;
	}


  DrawableButton drag_;
  DrawableButton drawLoopPoints_;
  DrawableButton setTime_;
  DrawableButton toggleSelection_;
  DrawableButton zoomIn_;

  typedef std::map<Mode::Action, DrawableButton*> ButtonMap;
  ButtonMap buttons_;

  DISALLOW_COPY_AND_ASSIGN(ModeSelector);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_MODESELECTOR__
