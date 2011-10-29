#ifndef __REC_SLOW_COMPONENTS__
#define __REC_SLOW_COMPONENTS__

#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/Slow.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {

namespace gui { class SongData; }

namespace gui { namespace audio { class Loops; }}
namespace gui { namespace audio { class PlayerController; }}
namespace gui { namespace audio { class TimeController; }}
namespace gui { namespace audio { class TransportController; }}

namespace widget { namespace tree { class Root; }}
namespace widget { namespace waveform { class Waveform; }}

namespace slow {

class Instance;
class MainPage;
class PlaybackController;

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

  ptr<widget::tree::Root> directoryTree_;
  ptr<widget::waveform::Waveform> waveform_;

  ptr<PlaybackController> playbackController_;
  ptr<MainPage> mainPage_;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMPONENTS__
