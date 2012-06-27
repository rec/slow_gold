#include "rec/widget/waveform/WaveformPainter.h"

#include "rec/util/FormatTime.h"
#include "rec/widget/Painter.h"
#include "rec/widget/waveform/Waveform.h"
#include "rec/widget/waveform/WaveformModel.h"

namespace rec {
namespace widget {
namespace waveform {

namespace {

// Skin

const int GRID_TEXT_WIDTH = 50;
const int GRID_TEXT_HEIGHT = 9;
const int GRID_TEXT_PAD = 4;

const int64 SMALLEST_TIME_SAMPLES = 10000;

}  // namespace

using namespace rec::util::block;

WaveformPainter::WaveformPainter(Waveform* w)
    : waveform_(w), thumbnail_(NULL), model_(w->model()){
}

void WaveformPainter::paint(Graphics& g, const Range<SampleTime >& range,
                            bool loading) {
  Painter p(model_.description().widget(), &g);
  if (!loading) {
    if (model_.isEmpty() || !thumbnail_) {
      g.setFont(14.0f);
      g.drawFittedText("Drop a file here or double-click to open a new file",
                       0, 0, waveform_->getWidth(),
                       waveform_->getHeight(),
                       juce::Justification::centred, 0);
    } else {
      drawWaveform(p, range);
      drawGrid(g, range);
    }
  }
}

SampleRate WaveformPainter::sampleRate() const {
  return model_.viewport().loop_points().sample_rate();
}

void WaveformPainter::drawWaveform(Painter& p,
                                   const Range<SampleTime>& range) {
  const BlockSet& selection = model_.selection();
  BlockSet::iterator i = selection.begin();
  Block r;
  r.first = SampleTime(range.begin_);
  r.second = SampleTime(range.end_);
  const juce::Rectangle<int>& bounds = waveform_->getLocalBounds();
  int channels = thumbnail_->getNumChannels();

  while (getSize(r) > 0) {
    for (; i != selection.end() && i->second <= r.first; ++i);
    bool selected = (i != selection.end() && r.first >= i->first);
    Block draw = r;
    if (selected)
      draw.second = i->second;

    else if (i != selection.end())
      draw.second = i->first;

    RealTime first(draw.first, sampleRate());
    RealTime second(draw.second, sampleRate());
    int x1 = model_.timeToX(draw.first);
    int x2 = model_.timeToX(draw.second);

    juce::Rectangle<int> b(x1, bounds.getY(), x2 - x1, bounds.getHeight());

    if (model_.description().parallel_waveforms() ||
        model_.description().layout() == WaveformProto::PARALLEL) {
      for (int i = 0; i < channels; ++i) {
        p.setColor(selected ? i + 1 : i + 1 + channels);
        thumbnail_->drawChannel(*p.graphics(), b, first, second, i, 1.0f);
      }
    } else {
      p.setColor(2 + (!selected) * 2);
      thumbnail_->drawChannels(*p.graphics(), b, first, second, 1.0f);
    }
    r.first = draw.second;
  }
}

void WaveformPainter::drawGrid(Graphics& g, const Range<SampleTime>& r) {
  SampleTime width(r.size());
  if (width < SMALLEST_TIME_SAMPLES) {
    LOG_FIRST_N(ERROR, 4) << "Nothing on screen! " << width;
    return;
  }
  double seconds = pow(10.0, floor(log10(RealTime(width, sampleRate()))));
  double samples = seconds * sampleRate();

  int b = static_cast<int>(ceil(r.begin_ / samples));
  int e = static_cast<int>(r.end_ / samples);
  int diff = e - b;

  if (diff <= 2)
    samples /= 2.0;
  else if (diff > 15)
    samples *= 5.0;

  if (samples > SampleTime(10.0, sampleRate()))
    samples *= 1.2;

  b = static_cast<int>(ceil(r.begin_ / samples));
  e = static_cast<int>(floor(r.end_ / samples));

  float h = static_cast<float>(waveform_->getHeight());
  int decimals = 0;
  if (samples < SampleTime(0.01, sampleRate()))
    decimals = 3;
  else if (samples < SampleTime(0.1, sampleRate()))
    decimals = 2;
  else if (samples < SampleTime(1.0, sampleRate()))
    decimals = 1;

  g.setFont(10);

  for (int i = b - 1; i <= e + 1; ++i) {
    SampleTime time = static_cast<int64>(i * samples);
    int x = model_.timeToX(time);

    if (model_.description().show_grid()) {
      g.setColour(juce::Colours::lightgreen.withAlpha(0.8f));
      g.drawVerticalLine(x, 0, h);
    }

    TimeFormat tf(TimeFormat::NO_FLASH, TimeFormat::NO_LEADING_ZEROS, decimals);
    String s = tf.format(time, model_.length(), sampleRate());
    g.setColour(juce::Colours::black);
    g.drawText(s, i ? x - GRID_TEXT_WIDTH / 2 : x - GRID_TEXT_WIDTH / 4,
               model_.description().show_times_at_top() ? GRID_TEXT_PAD :
               (static_cast<int>(h) - GRID_TEXT_PAD - GRID_TEXT_HEIGHT),
               GRID_TEXT_WIDTH,
               GRID_TEXT_HEIGHT,
               Justification::centred, true);
  }
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
