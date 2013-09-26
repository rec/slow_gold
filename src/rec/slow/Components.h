#ifndef __REC_SLOW_COMPONENTS__
#define __REC_SLOW_COMPONENTS__

#include "rec/music/Metadata.h"
#include "rec/data/DataListener.h"
#include "rec/gui/GetComponentMap.h"

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

class MainPage;

class Components : public data::DataListener<music::Metadata> {
 public:
  Components();
  ~Components();

  virtual void init();
  void setEnabled(bool enabled);
  virtual void operator()(const music::Metadata&);

  ApplicationCommandManager* manager_;
  unique_ptr<gui::audio::Loops> loops_;
  unique_ptr<gui::SongData> songData_;
  unique_ptr<gui::audio::TransformController> transformController_;
  unique_ptr<gui::audio::TransportController> transportController_;

  unique_ptr<widget::tree::Root> directoryTree_;
  unique_ptr<widget::waveform::Waveform> waveform_;

  unique_ptr<gui::audio::ModeSelector> modeSelector_;
  unique_ptr<gui::audio::CommandBar> commandBar_;
  unique_ptr<MainPage> mainPage_;
  gui::ComponentMap componentMap_;

  template <typename Type>
  Type* getComponent(const string& name) {
    try {
      Component* comp = componentMap_.at(name);
      if (Type* t = dynamic_cast<Type*>(comp))
        return t;
      LOG(DFATAL) << "Got component but couldn't cast for " << name;
    } catch (std::out_of_range&) {
      LOG(DFATAL) << "Couldn't get component for " << name;
    }
    return nullptr;
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(Components);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMPONENTS__
