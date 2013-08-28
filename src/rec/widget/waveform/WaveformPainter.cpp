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

using juce::Rectangle;

WaveformPainter::WaveformPainter(Waveform* w)
    : waveform_(w), thumbnail_(nullptr), model_(w->model()){
}

WaveformPainter::~WaveformPainter() {}

void WaveformPainter::drawEmpty(Graphics& g) {
  g.fillAll(juce::Colours::white);
  g.setFont(14.0f);
  g.drawFittedText("Drop a file here or double-click to open a new file",
                   0, 0, waveform_->getWidth(),
                   waveform_->getHeight(),
                   juce::Justification::centred, 0);
}

void WaveformPainter::paint(Graphics& g, const Range<SampleTime>& range,
                            bool isLoading) {
  if (isLoading || model_.isEmpty() || !thumbnail_) {
    drawEmpty(g);
  } else {
    painter_.reset(new Painter(model_.description().widget(), &g));
    range_ = range;
    bounds_ = waveform_->getLocalBounds();
    drawWaveform();
    drawGrid();
    painter_.reset();
  }
}

SampleRate WaveformPainter::sampleRate() const {
  return model_.viewport().loop_points().sample_rate();
}

void WaveformPainter::drawWaveform() {
  Restorer restore(*painter());

  int y = bounds_.getY();
  int height = bounds_.getHeight();
  drawWaveform(true);

  SampleRangeVector sel = model_.selection(true);
  for (SampleRangeVector::iterator i = sel.begin(); i != sel.end(); ++i)  {
    int x = model_.timeToX(i->begin_);
    int w = model_.timeToX(i->end_) - x;
    painter()->graphics()->excludeClipRegion(Rectangle<int>(x, y, w, height));
  }

  drawWaveform(false);
}

static const int CHANNELS = 2;

void WaveformPainter::drawWaveform(bool isSelected) {
  Graphics& g = *painter()->graphics();
  SampleRate rate(sampleRate());
  RealTime begin(range_.begin_, rate);
  RealTime end(range_.end_, rate);

  if (model_.description().parallel_waveforms() ||
      model_.description().layout() == WaveformProto::PARALLEL) {
    for (int i = 0; i < CHANNELS; ++i) {
      painter()->setColor(isSelected ? i + 1 : i + 1 + CHANNELS);
      thumbnail_->drawChannel(g, bounds_, begin, end, i, 1.0f);
    }
  } else {
    painter()->setColor(2 + (!isSelected) * 2);
    thumbnail_->drawChannels(g, bounds_, begin, end, 1.0f);
  }
}

void WaveformPainter::drawGrid() {
  Graphics& g = *painter()->graphics();
  SampleTime width(range_.size());
  if (width < SMALLEST_TIME_SAMPLES) {
    LOG_FIRST_N(ERROR, 4) << "Nothing on screen! " << width;
    return;
  }
  double seconds = pow(10.0, floor(log10(RealTime(width, sampleRate()))));
  double samples = seconds * sampleRate();

  int b = static_cast<int>(ceil(range_.begin_ / samples));
  int e = static_cast<int>(range_.end_ / samples);
  int diff = e - b;

  if (diff <= 2)
    samples /= 2.0;
  else if (diff > 15)
    samples *= 5.0;

  if (samples > SampleTime(10.0, sampleRate()))
    samples *= 1.2;

  b = static_cast<int>(ceil(range_.begin_ / samples));
  e = static_cast<int>(floor(range_.end_ / samples));

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
