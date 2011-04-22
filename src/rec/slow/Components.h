#ifndef __REC_SLOW_COMPONENTS__
#define __REC_SLOW_COMPONENTS__

#include "rec/gui/DropTarget.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/SongData.h"
#include "rec/gui/audio/StretchyController.h"
#include "rec/gui/audio/TimeController.h"
#include "rec/gui/audio/TransportController.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/PlaybackController.h"
#include "rec/util/thread/Trash.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace slow {

struct Instance;

struct Components {
  Components(Instance* i)
      : waveform_(widget::waveform::WaveformProto()),
        playbackController_(i),
        mainPage_(i) {
    playbackController_.setSetter(persist::appData<AppLayout>());
  }

  gui::audio::TimeController timeController_;

  gui::audio::Loops loops_;
  gui::SongData songData_;
  gui::audio::StretchyController stretchyController_;
  gui::audio::TransportController transportController_;

  widget::tree::Root directoryTree_;
  gui::DropTarget<widget::waveform::Waveform,
                  widget::waveform::WaveformProto> waveform_;

  PlaybackController playbackController_;
  MainPage mainPage_;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMPONENTS__
