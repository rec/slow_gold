#ifndef __REC_SLOW_COMPONENTS__
#define __REC_SLOW_COMPONENTS__

#include "rec/base/base.h"

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
  // DropTarget<Waveform, WaveformProto> waveform_;  // turn off dropping for now...

  MainPage mainPage_;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMPONENTS__
