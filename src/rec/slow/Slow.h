#ifndef __REC_SLOW_SLOW__
#define __REC_SLOW_SLOW__

#include "rec/base/base.h"

namespace rec {

namespace audio { class Device; }
namespace audio { namespace source { class Player; }}
namespace widget { namespace waveform { class Waveform; }}
namespace widget { namespace waveform { class WaveformProto; }}
namespace widget { namespace waveform { class ZoomProto; }}

namespace slow {

typedef audio::Device Device;
typedef audio::source::Player Player;

typedef widget::waveform::Waveform Waveform;
typedef widget::waveform::WaveformProto WaveformProto;
typedef widget::waveform::ZoomProto ZoomProto;

// typedef gui::DropTarget<Waveform, WaveformProto> WaveformDrop;

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_SLOW__
