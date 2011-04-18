#ifndef __REC_SLOW_COMPONENTS__
#define __REC_SLOW_COMPONENTS__

#include "rec/gui/DropTarget.h"
#include "rec/gui/Loops.h"
#include "rec/gui/SongData.h"
#include "rec/gui/StretchyController.h"
#include "rec/gui/TransportController.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/PlaybackController.h"
#include "rec/slow/TimeController.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace slow {

struct Instance;

struct Components {
  Components(Instance* instance) : waveform_(instance) {}

  PlaybackController playbackController_;
  TimeController timeController_;
  Waveform waveform_;

  gui::Loops loops_;
  gui::SongData songData_;
  gui::StretchyController stretchyController_;
  gui::TransportController transportController_;

  thread_ptr<widget::tree::Root> directoryTreeRoot_;
  DropTarget<Waveform, WaveformProto> waveform_;

  MainPage mainPage_;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMPONENTS__
