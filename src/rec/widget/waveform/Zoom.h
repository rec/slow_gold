#ifndef __REC_WIDGET_WAVEFORM_ZOOM__
#define __REC_WIDGET_WAVEFORM_ZOOM__

#include "rec/base/Samples.h"

namespace rec {
namespace widget {
namespace waveform {

class ZoomProto;

// The factor of k indicates how much wider or narrower the displayed area will
// be after the zoom.
void zoom(const VirtualFile& f, Samples<44100> length, double k);
void zoom(const VirtualFile& f, Samples<44100> length, Samples<44100> time, double k);

void constrainZoom(ZoomProto* z, Samples<44100> length);

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_ZOOM__
