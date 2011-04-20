#ifndef __REC_SLOW_COMPONENTS__
#define __REC_SLOW_COMPONENTS__

#include "rec/gui/DropTarget.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/audio/SongData.h"
#include "rec/gui/audio/StretchyController.h"
#include "rec/gui/audio/TransportController.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/PlaybackController.h"
#include "rec/slow/TimeController.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace slow {

struct Instance;

struct Components {
  Components(Instance* i) : playbackController_(i), waveform_(i) {
    playbackController_.setSetter(persist::data<AppLayout>());
  }

  PlaybackController playbackController_;
  TimeController timeController_;
  Waveform waveform_;

  gui::audio::Loops loops_;
  gui::audio::SongData songData_;
  gui::audio::StretchyController stretchyController_;
  gui::audio::TransportController transportController_;

  thread_ptr<widget::tree::Root> directoryTreeRoot_;
  DropTarget<Waveform, WaveformProto> waveform_;

  MainPage mainPage_;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMPONENTS__
