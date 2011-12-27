#ifndef __REC_SLOW_COMPONENTS__
#define __REC_SLOW_COMPONENTS__

#include "rec/base/base.h"

namespace rec {

namespace gui { class SongData; }

namespace gui { namespace audio { class CommandBar; } }
namespace gui { namespace audio { class Loops; } }
namespace gui { namespace audio { class ModeSelector; } }
namespace gui { namespace audio { class TransformController; } }
namespace gui { namespace audio { class TimeController; } }
namespace gui { namespace audio { class TransportController; } }

namespace widget { namespace tree { class Root; } }
namespace widget { namespace waveform { class Waveform; } }

namespace slow {

class Instance;
class MainPage;

class Components {
public:
  explicit Components(Instance*);
  ~Components();

  void setEnabled(bool enabled);

  ApplicationCommandManager* manager_;
  ptr<gui::audio::TimeController> timeController_;

  ptr<gui::audio::Loops> loops_;
  ptr<gui::SongData> songData_;
  ptr<gui::audio::TransformController> transformController_;
  ptr<gui::audio::TransportController> transportController_;

  ptr<widget::tree::Root> directoryTree_;
  ptr<widget::waveform::Waveform> waveform_;

  ptr<gui::audio::ModeSelector> modeSelector_;
  ptr<gui::audio::CommandBar> commandBar_;
  ptr<MainPage> mainPage_;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMPONENTS__
