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
  WaveformPainter(Waveform* w) : waveform_(w), thumbnail_(NULL) {}
  void paint(Graphics&);

  void setAudioThumbnail(juce::AudioThumbnail* t) { thumbnail_ = t; }

 private:
  void drawWaveform(Painter& g, const Range<Samples<44100> >&);
  void drawGrid(Graphics& g, const Range<Samples<44100> >&);

  Waveform* waveform_;
  juce::AudioThumbnail* thumbnail_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(WaveformPainter);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_WAVEFORMPAINTER__
