#ifndef __REC_WIDGET_WAVEFORM_VIEWPORT__
#define __REC_WIDGET_WAVEFORM_VIEWPORT__

#include "rec/base/base.h"
#include "rec/base/Samples.h"

namespace rec {
namespace widget {
namespace waveform {

void addLoopPointToViewport(const VirtualFile& file, Samples<44100> time);

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_VIEWPORT__
