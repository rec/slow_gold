#ifndef __REC_SLOW_COMPONENTS__
#define __REC_SLOW_COMPONENTS__

#include "rec/gui/DropTarget.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/SongData.h"
#include "rec/gui/audio/PlayerController.h"
#include "rec/gui/audio/TimeController.h"
#include "rec/gui/audio/TransportController.h"
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
namespace slow {

typedef gui::DropTarget<Waveform> WaveformComp;

struct Components {
  Components(Instance* instance)
    : manager_(instance->target_->targetManager()->commandManager()),
      loops_(manager_),
      songData_(manager_),
      directoryTree_(manager_),
      playbackController_(this),
      mainPage_(this) {
    playbackController_.setSetter(persist::setterGlobal<AppLayout>());
    waveform_.setManager(manager_);
  }

  ApplicationCommandManager* manager_;
  gui::audio::TimeController timeController_;

  gui::audio::Loops loops_;
  gui::SongData songData_;
  gui::audio::PlayerController playerController_;
  gui::audio::TransportController transportController_;

  widget::tree::Root directoryTree_;
  WaveformComp waveform_;

  PlaybackController playbackController_;
  MainPage mainPage_;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMPONENTS__
