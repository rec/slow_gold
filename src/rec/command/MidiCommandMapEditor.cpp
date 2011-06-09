#if 0

#include "rec/command/MidiCommandMapEditor.h"

namespace rec {
namespace command {

MidiCommandMapEditor::MidiCommandMapEditor(ApplicationCommandManager& commandManager,
                                           MidiCommandMap& mappingSet,
                                           ChangeBroadcaster& broadcaster)
    : CommandMapEditor(commandManager, broadcaster), mappings(mappingSet) {
}

void MidiCommandMapEditor::addButton(CommandMapEditButton* button) {
}

void MidiCommandMapEditor::removeButton(CommandMapEditButton* button) {
}

void MidiCommandMapEditor::addChildren(CommandMapItemComponent* comp) {
  const bool isReadOnly = isCommandReadOnly(comp->commandID);
  const Array <MidiPress> keyPresses (getMappings().getMidiPressesAssignedToCommand (comp->commandID));
  for (int i = 0; i < jmin ((int) MAX_NUM_ASSIGNMENTS, keyPresses.size()); ++i)
    comp->addMidiPressButton (getDescriptionForMidiPress (keyPresses.getReference (i)), i, isReadOnly);
  comp->addMidiPressButton (String::empty, -1, isReadOnly);
}



static void assignNewMidiCallback (int result, CommandMapEditButton* button, MidiPress newMidi)
{
     if (result != 0 && button != nullptr) {
         MidiCommandMapEditor* editor = dynamic_cast<MidiCommandMapEditor*>(&button->getOwner());
         editor->setNewMidi (button, newMidi, true);
     }
}

static void setNewMidi (MidiPressMappingSet& mappings, CommandMapEditButton* button,
                       const MidiPress& newMidi, bool dontAskUser)
{
    if (newMidi.isValid())
    {
        const CommandID previousCommand = mappings.findCommandForMidiPress (newMidi);

        if (previousCommand == 0 || dontAskUser)
        {
            mappings.removeMidiPress (newMidi);

            if (button->keyNum >= 0)
                mappings.removeMidiPress (button->commandID, button->keyNum);

            mappings.addMidiPress (button->commandID, newMidi, button->keyNum);
        }
        else
        {
            AlertWindow::showOkCancelBox (AlertWindow::WarningIcon,
                                          TRANS("Change key-mapping"),
                                          TRANS("This key is already assigned to the command \"")
                                            + mappings.getCommandManager()->getNameOfCommand (previousCommand)
                                            + TRANS("\"\n\nDo you want to re-assign it to this new command instead?"),
                                          TRANS("Re-assign"),
                                          TRANS("Cancel"),
                                          this,
                                          ModalCallbackFunction::forComponent (assignNewMidiCallback,
                                                                               button, MidiPress (newMidi)));
        }
    }
}

void keyChosen (int result, CommandMapEditButton* button)
{
    MidiCommandEntryWindow* window = dynamic_cast<MidiCommandEntryWindow*>(button->getCommandEntryWindow());
    if (result != 0 && button != nullptr && window != nullptr)
    {
        window->setVisible (false);
        setNewMidi (window->owner.getMappings(), button, window->lastPress, false);
    }

    button->setCommandEntryWindow();
}

void MidiCommandMapEditor::addButton(CommandMapEditButton* button)
{
    button->setCommandEntryWindow(new MidiCommandEntryWindow(*this));
    button->getCommandEntryWindow()->enterModalState (true, ModalCallbackFunction::forComponent(keyChosen, button));
}

void MidiCommandMapEditor::removeButton(CommandMapEditButton* button)
{
    getMappings().removeMidiPress(button->commandID, button->keyNum);
}

}  // namespace command
}  // namespace rec

#endif