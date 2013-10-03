#ifndef __REC_WIDGET_WAVEFORM_VIEWPORT__
#define __REC_WIDGET_WAVEFORM_VIEWPORT__

#include "rec/base/base.h"
#include "rec/base/SampleTime.h"

namespace rec {
namespace widget {
namespace waveform {

class Viewport;

void addLoopPointToViewport(const VirtualFile& file, SampleTime time);
double selectionInZoom(const Viewport&);


}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_VIEWPORT__
