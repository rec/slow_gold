#ifndef __REC_SLOW_COMPONENTS__
#define __REC_SLOW_COMPONENTS__

#include "rec/base/base.h"

namespace rec {
namespace slow {

struct Instance;

struct Components {
  Components(Instance* instance) : instance_(instance) {
  }

  MainPage mainPage_;
  PlaybackController playbackController_;
  TimeController timeController_;
  Waveform waveform_;

  gui::AudioSetupPage audioSetupPage_;
  gui::Loops loops_;
  gui::SongData songData_;
  gui::StretchyController stretchyController_;
  gui::TransportController transportController_;

  thread_ptr<widget::tree::Root> directoryTreeRoot_;

  // DropTarget<Waveform, WaveformProto> waveform_;  // turn off dropping for now...
};

#if 0
      directoryTreeRoot_(new Root(widget::tree::NodeDesc())),
      waveform_(instance_, WaveformProto()),
      playbackController_(instance_, stretchyPlayer_.getTransport()),
      openDialogOpen_(false),
      audioSetupPage_(instance_->device_) {
#endif

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_COMPONENTS__
