#ifndef __REC_SLOW_COMPONENTS__
#define __REC_SLOW_COMPONENTS__

#include "rec/gui/DropTarget.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/PlaybackController.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Slow.h"
#include "rec/slow/Target.h"
#include "rec/util/thread/Trash.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {

namespace gui { class SongData; }

namespace gui { namespace audio { class Loops; }}
namespace gui { namespace audio { class PlayerController; }}
namespace gui { namespace audio { class TimeController; }}
namespace gui { namespace audio { class TransportController; }}

namespace slow {

typedef gui::DropTarget<Waveform> WaveformComp;

struct Components {
  explicit Components(Instance*);
  ~Components();
  void setActive(bool);

  ApplicationCommandManager* manager_;
  ptr<gui::audio::TimeController> timeController_;

  ptr<gui::audio::Loops> loops_;
  ptr<gui::SongData> songData_;
  ptr<gui::audio::PlayerController> playerController_;
  ptr<gui::audio::TransportController> transportController_;

  widget::tree::Root directoryTree_;
  WaveformComp waveform_;

  PlaybackController playbackController_;
  MainPage mainPage_;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMPONENTS__
