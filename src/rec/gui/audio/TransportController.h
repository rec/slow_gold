#ifndef __REC_GUI_AUDIO_TRANSPORTCONTROLLER__
#define __REC_GUI_AUDIO_TRANSPORTCONTROLLER__

#include "rec/audio/Audio.h"
#include "rec/audio/source/Player.h"
#include "rec/command/Command.pb.h"
#include "rec/gui/LanguageButton.h"
#include "rec/gui/DataSlider.h"
#include "rec/gui/SetterToggle.h"
#include "rec/gui/audio/LevelMeter.h"
#include "rec/gui/proto/Panel.h"
#include "rec/util/Listener.h"
#include "rec/util/StateListener.h"

namespace rec {
namespace gui {
namespace audio {

class TimeController;

enum TransportCommand {
  TOGGLE_START_STOP,
  JUMP_TO_FIRST,
  JUMP_TO_PREVIOUS,
  JUMP_TO_NEXT,
};

// A GUI component with three drawable buttons that broadcasts commands from
// those buttons.
class TransportController : public Panel {
 public:
  TransportController();
  virtual ~TransportController();

 private:
  unique_ptr<Component> gainPanel_;
  unique_ptr<Component> buttonsPanel_;
  LevelMeter levelMeter_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TransportController);
};

}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_GUI_AUDIO_TRANSPORTCONTROLLER__
