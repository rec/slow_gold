#ifndef __REC_WIDGET_WAVEFORM_WAVEFORMPAINTER__
#define __REC_WIDGET_WAVEFORM_WAVEFORMPAINTER__

#include "rec/base/SampleRate.h"
#include "rec/base/SampleTime.h"
#include "rec/util/Range.h"

namespace rec {
namespace widget {

class Painter;

namespace waveform {

class Waveform;
class WaveformModel;

class WaveformPainter {
 public:
  WaveformPainter(Waveform* w);
  void paint(Graphics&, const Range<SampleTime >&, bool loading);

  void setAudioThumbnail(juce::AudioThumbnail* t) { thumbnail_ = t; }

 private:
  SampleRate sampleRate() const;

  void drawWaveform(Painter& g, const Range<SampleTime >&);
  void drawGrid(Graphics& g, const Range<SampleTime >&);

  Waveform* waveform_;
  juce::AudioThumbnail* thumbnail_;
  const WaveformModel& model_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(WaveformPainter);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_WAVEFORMPAINTER__
