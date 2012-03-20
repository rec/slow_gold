#ifndef __REC_WIDGET_WAVEFORM_WAVEFORMPAINTER__
#define __REC_WIDGET_WAVEFORM_WAVEFORMPAINTER__

#include "rec/base/Samples.h"
#include "rec/util/Range.h"

namespace rec {
namespace widget {

class Painter;

namespace waveform {

class Waveform;

class WaveformPainter {
 public:
  WaveformPainter(Waveform* waveform) : waveform_(waveform) {}
  void paint(Graphics&);

 private:
  void drawWaveform(Painter& g, const Range<Samples<44100> >&);
  void drawGrid(Graphics& g, const Range<Samples<44100> >&);

  Waveform* waveform_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(WaveformPainter);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_WAVEFORMPAINTER__
