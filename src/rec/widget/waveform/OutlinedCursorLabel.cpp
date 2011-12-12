#include "rec/widget/waveform/OutlinedCursorLabel.h"
#include "rec/widget/waveform/Waveform.pb.h"
#include "rec/widget/waveform/Cursor.h"

namespace rec {
namespace widget {
namespace waveform {

static const float INSET = 1.0f;
static const float CORNER = 3.0f;
static const float LINE_WIDTH = 0.6f;

OutlinedCursorLabel::OutlinedCursorLabel(Cursor *cursor)
    : cursor_(cursor) {
  requestUpdates();
  selectButton_.addButtonListener(this);
}

OutlinedCursorLabel::~OutlinedCursorLabel() {
}

void OutlinedCursorLabel::onDataChange(const WaveformProto& waveform) {
  thread::callAsync(this, &OutlinedCursorLabel::showSelectButton,
                    waveform.show_selection_buttons());
}

void OutlinedCursorLabel::showSelectButton(bool sel) {
  if (sel)
    addAndMakeVisible(&selectButton_);
  else
    removeChildComponent(&selectButton_);

  cursor_->resizeCaption();
  cursor_->repaint();
}

void OutlinedCursorLabel::resized() {
  gui::SimpleLabel::resized();
  selectButton_.setSize(getHeight(), getHeight());
}

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
  selectButton_.setToggleState(selected, false);
}

void OutlinedCursorLabel::buttonClicked(juce::Button*) {
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
