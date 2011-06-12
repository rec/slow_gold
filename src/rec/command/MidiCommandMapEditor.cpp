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
    listen(this);
  }

  void listen(bool on) { mappings_->requestOneMessage(on ? this : NULL); }

  virtual ~MidiCommandEntryWindow() { listen(false); }

  virtual void operator()(const MidiMessage& msg) {
    if (msg.isNoteOn() || msg.isProgramChange() || msg.isController()) {
      lastKey_ = msg;
      MessageManagerLock l;
      setMessage(owner_->getKeyMessage(msg));
    }

    mappings_->requestOneMessage(this);
  }

	MidiCommandMapEditor* owner() { return owner_; }
  MidiMessage lastKey_;

 private:
  MidiCommandMapEditor* owner_;
  MidiCommandMap* mappings_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(MidiCommandEntryWindow);
};

}  // namespace

template <>
const String MidiCommandMapEditor::name() {
  return "Midi";
}

template <>
const String MidiCommandMapEditor::getDescription(const MidiMessage& key) {
  return midiName(key);
}

template <>
void MidiCommandMapEditor::removeKey(CommandID command, int keyNum) {
  mappings.removeCommand(static_cast<Command::Type>(command), keyNum);
  mappings.sendChangeMessage();
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
  return static_cast<CommandID>(mappings.getCommand(mappings.toBytes(key)));
}

template <>
void MidiCommandMapEditor::removeKey(const MidiMessage& key) {
  mappings.removeKey(mappings.toBytes(key));
  mappings.sendChangeMessage();
}

template <>
void MidiCommandMapEditor::addKey(CommandID cmd, const MidiMessage& key, int keyIndex) {
  mappings.add(mappings.toBytes(key), static_cast<Command::Type>(cmd), keyIndex);
  mappings.sendChangeMessage();
}

template <>
void MidiCommandMapEditor::keyChosen(int result, CommandMapEditButton* button)
{
    MidiCommandEntryWindow* window = dynamic_cast<MidiCommandEntryWindow*>(button->getCommandEntryWindow());
    if (result != 0 && button != nullptr && window != nullptr) {
        window->setVisible (false);
        window->owner()->setNewKey (button, window->lastKey_, false);
    }
    if (window)
      window->listen(false);

    button->setCommandEntryWindow();
}


template <>
void MidiCommandMapEditor::assignNewKeyCallback(int result, CommandMapEditButton* button, MidiMessage key) {
     if (result != 0 && button != nullptr) {
         MidiCommandMapEditor* editor = dynamic_cast<MidiCommandMapEditor*>(&button->getOwner());
         editor->setNewKey (button, key, true);
     }
}

}  // namespace command
}  // namespace rec

