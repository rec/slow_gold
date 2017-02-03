#pragma once

#include "rec/base/SampleRate.h"
#include "rec/base/SampleTime.h"
#include "rec/util/Loading.h"
#include "rec/util/range/Range.h"

namespace rec {
namespace widget {

class Painter;

namespace waveform {

class Waveform;
class WaveformModel;

class WaveformPainter {
  public:
    WaveformPainter(Waveform* w);
    ~WaveformPainter();

    void paint(Graphics&, const Range<SampleTime >&, Loading);

    void setAudioThumbnail(juce::AudioThumbnail* t) { thumbnail_ = t; }

  private:
    SampleRate sampleRate() const;

    void drawWaveform();
    void drawWaveform(bool isSelected);

    void drawGrid();
    void drawEmpty(Graphics& g);
    Painter* painter() { return painter_.get(); }

    Waveform* waveform_;
    juce::AudioThumbnail* thumbnail_;
    const WaveformModel& model_;
    Range<SampleTime> range_;
    std::unique_ptr<Painter> painter_;
    juce::Rectangle<int> bounds_;

    DISALLOW_COPY_ASSIGN_AND_LEAKS(WaveformPainter);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec
