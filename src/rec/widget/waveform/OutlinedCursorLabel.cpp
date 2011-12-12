#include "rec/widget/waveform/OutlinedCursorLabel.h"

namespace rec {
namespace widget {
namespace waveform {

static const float INSET = 1.0f;
static const float CORNER = 3.0f;
static const float LINE_WIDTH = 0.6f;

void OutlinedCursorLabel::paint(Graphics& g) {
  juce::Rectangle<int> bounds = getLocalBounds();
  juce::Rectangle<float> b;
  b.setX(INSET);
  b.setY(INSET);
  b.setWidth(bounds.getWidth() - 2 * INSET);
  b.setHeight(bounds.getHeight() - 2 * INSET);

  g.setColour(juce::Colours::white);
  g.fillRoundedRectangle(b, CORNER);

  g.setColour(juce::Colours::black);

  g.drawRoundedRectangle(b, CORNER, LINE_WIDTH);
  gui::SimpleLabel::paint(g);
}

void OutlinedCursorLabel::setSelected(bool selected) {
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
