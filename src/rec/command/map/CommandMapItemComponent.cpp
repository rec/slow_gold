#include "rec/command/map/CommandMapItemComponent.h"
#include "rec/command/map/CommandMapEditButton.h"

namespace rec {
namespace command {

CommandMapItemComponent::CommandMapItemComponent(CommandMapEditor& owner_,
                                                 const CommandID commandID_)
    : commandID (commandID_), owner(owner_) {
  setInterceptsMouseClicks (false, true);

  owner.addChildren(this);
}

void CommandMapItemComponent::addButton(const String& desc, const int index, const bool isReadOnly)
{
  CommandMapEditButton* const b = new CommandMapEditButton(owner, commandID, desc, index);
  buttons.add (b);

  b->setEnabled (! isReadOnly);
  b->setVisible (buttons.size() <= (int) maxNumAssignments);
  addChildComponent (b);
}

void CommandMapItemComponent::paint(Graphics& g) {
  g.setFont (getHeight() * 0.7f);
  g.setColour (findColour (CommandMapEditor::textColourId));

  g.drawFittedText (owner.getCommandManager().getNameOfCommand (commandID),
                    4, 0, jmax (40, getChildComponent (0)->getX() - 5), getHeight(),
                    Justification::centredLeft, true);
}

void CommandMapItemComponent::resized() {
  int x = getWidth() - 4;

  for (int i = buttons.size(); --i >= 0;)
  {
      CommandMapEditButton* const b = buttons.getUnchecked(i);

      b->fitToContent (getHeight() - 2);
      b->setTopRightPosition (x, 1);
      x = b->getX() - 5;
  }
}

}  // namespace command
}  // namespace rec

