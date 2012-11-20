#include "rec/command/map/CommandMapItemComponent.h"
#include "rec/command/map/CommandMapEditButton.h"

namespace rec {
namespace command {

namespace {

const float HEIGHT_RATIO = 0.7f;
const int TEXT_X_MARGIN = 4;
const int TEXT_X_OFFSET = 1;
const int TEXT_X_TOTAL = TEXT_X_MARGIN + TEXT_X_OFFSET;
const int TEXT_WIDTH_MAX = 40;
const int TEXT_Y_MARGIN = 1;

}  // namespace

CommandMapItemComponent::CommandMapItemComponent(CommandMapEditor& owner,
                                                 const CommandID commandID)
    : commandID_(commandID), owner_(owner) {
  setInterceptsMouseClicks (false, true);
  owner.addChildren(this);
}

void CommandMapItemComponent::addButton(const String& desc, int index,
                                        bool isReadOnly) {
  CommandMapEditButton* const b = new CommandMapEditButton(owner_, commandID_,
                                                           desc, index);
  buttons_.add (b);

  b->setEnabled(!isReadOnly);
  b->setVisible(buttons_.size() <= (int) maxNumAssignments);
  addChildComponent(b);
}

void CommandMapItemComponent::paint(Graphics& g) {
  g.setFont(getHeight() * HEIGHT_RATIO);
  g.setColour(findColour(CommandMapEditor::textColourId));

  g.drawFittedText(owner_.getCommandManager().getNameOfCommand(commandID_),
                   TEXT_X_MARGIN, 0,
                   jmax(TEXT_WIDTH_MAX,
                        getChildComponent(0)->getX() - TEXT_X_TOTAL),
                   getHeight(),
                   Justification::centredLeft, true);
}

void CommandMapItemComponent::resized() {
  int x = getWidth() - TEXT_X_MARGIN;

  for (int i = buttons_.size(); --i >= 0;) {
    CommandMapEditButton* const b = buttons_.getUnchecked(i);

    b->fitToContent(getHeight() - 2 * TEXT_Y_MARGIN);
    b->setTopRightPosition(x, TEXT_Y_MARGIN);
    x = b->getX() - TEXT_X_TOTAL;
  }
}

}  // namespace command
}  // namespace rec

