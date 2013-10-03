#ifndef __REC_WIDGET_WAVEFORM_VIEWPORT__
#define __REC_WIDGET_WAVEFORM_VIEWPORT__

#include "rec/base/base.h"
#include "rec/base/SampleTime.h"

namespace rec {
namespace widget {
namespace waveform {

class Viewport;

void addLoopPointToViewport(const VirtualFile& file, SampleTime time);

// If greater than 1, the selection is not contained within the zoom.
// Otherwise, returns the ratio between the selection area and the zoomed area.
double selectionInZoom(const Viewport&);

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_VIEWPORT__
