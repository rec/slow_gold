#ifndef __REC_SLOW_BROADCASTERS__
#define __REC_SLOW_BROADCASTERS__

#include "rec/audio/Audio.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/gui/LoopPoint.pb.h"
#include "rec/util/ClockUpdate.h"
#include "rec/util/Range.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/listener/Listener.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace slow {

struct Broadcasters {
  Broadcaster<const ClockUpdate&> clockUpdate_;
  Broadcaster<const SelectionRange&> selectionRange_;
  Broadcaster<const audio::stretch::StretchLoop&> stretchLoop_;
  Broadcaster<const file::VirtualFile&> virtualFile_;
  Broadcaster<const file::VirtualFileList&> virtualFileList_;
  Broadcaster<const gui::LoopPointList&> loopPointList_;
  Broadcaster<const widget::waveform::CursorTime&> cursorTime_;
  Broadcaster<const widget::waveform::TimeAndMouseEvent&> timeAndMouseEvent_;
  Broadcaster<const widget::waveform::ZoomProto&> zoomProto_;

  Broadcaster<RealTime> realTime_;
  Broadcaster<TransportState> transportState_;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_BROADCASTERS__
