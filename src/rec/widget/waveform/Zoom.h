#ifndef __REC_WIDGET_WAVEFORM_ZOOM__
#define __REC_WIDGET_WAVEFORM_ZOOM__

#include "rec/base/Samples.h"

namespace rec {
namespace widget {
namespace waveform {

class Zoom;

static const Samples<41000> MIN_ZOOM_TIME = 4 * 44100;

// The factor of k indicates how much wider or narrower the displayed area will
// be after the zoom.
void zoom(const VirtualFile& f, Samples<44100> length, double k);
void zoom(const VirtualFile& f, Samples<44100> length, Samples<44100> time, double k);
void zoomTo(const VirtualFile& f, Samples<44100> begin, Samples<44100> end,
            Samples<44100> length);
void zoomOutFull(const VirtualFile& f, Samples<44100> length);

void constrainZoom(Zoom* z, Samples<44100> length);

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_ZOOM__
