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

template <>
CommandEntryWindow* MidiCommandMapEditor::newWindow() {
  return new CommandEntryWindow("Waiting for a MIDI message");
}

template <>
const Array<MidiMessage> MidiCommandMapEditor::getKeys(CommandID cmd) {
  Array<MidiMessage> result;
  const vector<string> keys = mappings.getKeys(static_cast<Command::Type>(cmd));
  for (vector<string>::const_iterator i = keys.begin(); i != keys.end(); ++i)
    result.add(MidiMessage(i->data(), i->size()));

  return result;
}

template <>
CommandID MidiCommandMapEditor::getCommand(const MidiMessage& key) {
  return static_cast<CommandID>(mappings.getCommand(str(key)));
}

template <>
void MidiCommandMapEditor::removeKey(const MidiMessage& key) {
  mappings.removeKey(str(key));
}

#if 0

template <>
void MidiCommandMapEditor::addKey(CommandID cmd, const MidiMessage& key, int keyIndex) {
  mappings.addMidiMessage(cmd, key, keyIndex);
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

