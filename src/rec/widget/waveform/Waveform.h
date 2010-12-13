#ifndef __REC_WIDGET_WAVEFORM__
#define __REC_WIDGET_WAVEFORM__

#include "rec/widget/Waveform.pb.h"
#include "rec/util/listener/Broadcaster.h"
#include "rec/widget/Painter.h"
#include "rec/widget/tree/VolumeFile.h"

namespace rec {
namespace widget {
namespace waveform {

// This handles waveform display only (no command information).
class Waveform : public Component {
 public:
  explicit Waveform(const WaveformProto& desc) : desc_(desc) {}

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(WaveformProto);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM__
