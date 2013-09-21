#include "rec/widget/waveform/OutlinedCursorLabel.h"

#include "rec/data/DataCenter.h"
#include "rec/data/UndoStack.h"
#include "rec/util/thread/CallAsync.h"
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
  DCHECK(cursor);
  selectButton_.addListener(this);
  setEditable(true, false, false);
}

OutlinedCursorLabel::~OutlinedCursorLabel() {}

void OutlinedCursorLabel::operator()(const WaveformProto& waveform) {
  showSelectionButtons_ = waveform.show_selection_buttons();
  if (showSelectionButtons_)
    addAndMakeVisible(&selectButton_);
  else
    removeChildComponent(&selectButton_);

  setVisible(waveform.show_cursor_labels());

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
  selectButton_.setToggleState(selected, juce::dontSendNotification);
}

void OutlinedCursorLabel::buttonClicked(juce::Button* b) {
  cursor_->selectButtonPressed(b->getToggleState());
}

void OutlinedCursorLabel::textEditorTextChanged(TextEditor& e) {
  gui::SimpleLabel::textEditorTextChanged(e);
  cursor_->setText(e.getText());
}

static const bool FIX = true;

void OutlinedCursorLabel::editorShown(TextEditor*) {
  if (showSelectionButtons_)
    removeChildComponent(&selectButton_);
  data::getDataCenter()->undoStack()->startGroup();
}

void OutlinedCursorLabel::editorAboutToBeHidden(TextEditor*) {
  data::getDataCenter()->undoStack()->stopGroup();
  if (showSelectionButtons_)
    addAndMakeVisible(&selectButton_);
}

}  // namespace waveform
}  // namespace widget
}  // namespace rec
