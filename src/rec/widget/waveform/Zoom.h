#pragma once

#include "rec/base/SampleTime.h"

namespace rec {
namespace widget {
namespace waveform {

class Zoom;

// The factor of k indicates how much wider or narrower the displayed area will
// be after the zoom.
void zoomScale(const VirtualFile& f, SampleTime length, SampleRate rate,
               double k);

void zoomScaleAt(const VirtualFile& f, SampleTime length, SampleRate rate,
                 double k, SampleTime time);

void zoomTo(const VirtualFile& f, SampleTime length, SampleRate rate,
            SampleTime begin, SampleTime end);

void zoomOutFull(const VirtualFile& f, SampleTime length);

void constrainZoom(Zoom* z, SampleTime length, SampleRate rate);

}  // namespace waveform
}  // namespace widget
}  // namespace rec

