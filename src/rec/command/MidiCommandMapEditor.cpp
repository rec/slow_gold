#include "rec/command/MidiCommandMapEditor.h"

#include "rec/audio/Device.h"
#include "rec/command/MidiName.h"
#include "rec/util/listener/Listener.h"

namespace rec {
namespace command {

namespace {

class MidiCommandEntryWindow : public CommandEntryWindow,
                               public Listener<const MidiMessage&> {
 public:
  explicit MidiCommandEntryWindow(MidiCommandMapEditor* owner)
      : CommandEntryWindow("Waiting for a MIDI note, program change or controller..."),
        owner_(owner),
        mappings_(&owner->getMappings()) {
    mappings_->requestOneMessage(this);
  }

  virtual ~MidiCommandEntryWindow() {
    if (lastMidi_.isActiveSense())
      mappings_->requestOneMessage(NULL);
  }

  virtual void operator()(const MidiMessage& msg) {
    if (!(msg.isNoteOn() || msg.isProgramChange() || msg.isController())) {
      mappings_->requestOneMessage(this);
    } else {
      lastMidi_ = msg;
      exitModalState(0);
    }
  }

  const MidiMessage& lastMidi() { return lastMidi_; }
	MidiCommandMapEditor* owner() { return owner_; }
  
 private:
  MidiMessage lastMidi_;
  MidiCommandMapEditor* owner_;
  MidiCommandMap* mappings_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(MidiCommandEntryWindow);
};

}  // namespace

template <>
const String MidiCommandMapEditor::getDescription(const MidiMessage& key) {
  return midiName(key);
}

template <>
void MidiCommandMapEditor::removeKey(CommandID command, int keyNum) {
  mappings.removeCommand(static_cast<Command::Type>(command), keyNum);
}

template <>
bool MidiCommandMapEditor::isValid(const MidiMessage& key) {
  return true;
}

template <>
CommandEntryWindow* MidiCommandMapEditor::newWindow() {
  return new MidiCommandEntryWindow(this);
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

template <>
void MidiCommandMapEditor::addKey(CommandID cmd, const MidiMessage& key, int keyIndex) {
  mappings.add(str(key), static_cast<Command::Type>(cmd), keyIndex);
}

template <>
void MidiCommandMapEditor::keyChosen(int result, CommandMapEditButton* button)
{
    MidiCommandEntryWindow* window = dynamic_cast<MidiCommandEntryWindow*>(button->getCommandEntryWindow());
    if (result != 0 && button != nullptr && window != nullptr) {
        window->setVisible (false);
        window->owner()->setNewKey (button, window->lastMidi(), false);
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

#if 0
#endif

}  // namespace command
}  // namespace rec

