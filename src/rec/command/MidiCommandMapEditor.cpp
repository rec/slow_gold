#include "rec/command/MidiCommandMapEditor.h"
#include "rec/command/MidiName.h"

namespace rec {
namespace command {

template <>
const String MidiCommandMapEditor::getDescription(const MidiMessage& key) {
  return midiName(key);
}

template <>
void MidiCommandMapEditor::removeKey(CommandID command, int keyNum) {
  mappings.removeMessage(static_cast<Command::Type>(command), keyNum);
}

template <>
bool MidiCommandMapEditor::isValid(const MidiMessage& key) {
  return true;
}

#if 0

template <>
const Array<MidiMessage> MidiCommandMapEditor::getKeys(CommandID cmd) {
  return mappings.getMidiMessageesAssignedToCommand(cmd);
}

template <>
CommandID MidiCommandMapEditor::getCommand(const MidiMessage& key) {
  return mappings.findCommandForMidiMessage (key);
}

template <>
void MidiCommandMapEditor::removeKey(const MidiMessage& key) {
  mappings.removeMidiMessage (key);
}

template <>
void MidiCommandMapEditor::addKey(CommandID cmd, const MidiMessage& key, int keyIndex) {
  mappings.addMidiMessage(cmd, key, keyIndex);
}

template <>
CommandEntryWindow* MidiCommandMapEditor::newWindow() {
  return new KeyCommandEntryWindow(*this);
}

template <>
void MidiCommandMapEditor::keyChosen (int result, CommandMapEditButton* button)
{
    KeyCommandEntryWindow* window = dynamic_cast<KeyCommandEntryWindow*>(button->getCommandEntryWindow());
    if (result != 0 && button != nullptr && window != nullptr)
    {
        window->setVisible (false);
        window->owner.setNewKey (button, window->lastPress, false);
    }

    button->setCommandEntryWindow();
}

template <>
void MidiCommandMapEditor::assignNewKeyCallback(int result, CommandMapEditButton* button, MidiMessage key) {
     if (result != 0 && button != nullptr) {
         MidiCommandMapEditor* editor = dynamic_cast<MidiCommandMapEditor*>(&button->getOwner());
         editor->setNewKey (button, key, true);
     }
}

#endif

}  // namespace command
}  // namespace rec

