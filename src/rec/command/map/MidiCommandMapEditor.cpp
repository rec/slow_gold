#include "rec/command/map/MidiCommandMapEditor.h"

#include "rec/audio/Device.h"
#include "rec/base/Trans.h"
#include "rec/command/map/MidiName.h"
#include "rec/util/Listener.h"
#include "rec/util/thread/CallAsync.h"

TRAN(WAITING, "Waiting for a MIDI note, program change or controller...");
TRAN(MIDI, "MIDI");

namespace rec {
namespace command {

namespace {

class MidiCommandEntryWindow : public CommandEntryWindow,
                               public Listener<const MidiMessage&> {
 public:
  explicit MidiCommandEntryWindow(MidiCommandMapEditor* owner)
      : CommandEntryWindow(t_WAITING),
        lastKeyEntered_(false),
        owner_(owner),
        mappings_(&owner->getMappings()) {
    listen(true);
  }

  void listen(bool on) { mappings_->requestOneMessage(on ? this : NULL); }

  virtual ~MidiCommandEntryWindow() { listen(false); }

  virtual void operator()(const MidiMessage& msg) {
    if (msg.isNoteOn() || msg.isProgramChange() || msg.isController()) {
      lastKey_ = msg;
      lastKeyEntered_ = true;
      thread::callAsync(this, &CommandEntryWindow::setMessage,
                        owner_->getKeyMessage(msg));
    }

    mappings_->requestOneMessage(this);
  }

	MidiCommandMapEditor* owner() { return owner_; }
  MidiMessage lastKey_;
  bool lastKeyEntered_;

 private:
  MidiCommandMapEditor* owner_;
  MidiCommandMap* mappings_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(MidiCommandEntryWindow);
};

}  // namespace

template <>
const String MidiCommandMapEditor::name() {
  return t_MIDI;
}

template <>
const String MidiCommandMapEditor::getDescription(const MidiMessage& key) {
  return midiName(key);
}

template <>
void MidiCommandMapEditor::removeKey(CommandID command, int keyNum) {
  mappings_.removeCommand(static_cast<Command::Type>(command), keyNum);
  mappings_.sendChangeMessage();
}

template <>
bool MidiCommandMapEditor::isValid(const MidiMessage&) {
  return true;
}

template <>
CommandEntryWindow* MidiCommandMapEditor::newWindow() {
  return new MidiCommandEntryWindow(this);
}

template <>
const Array<MidiMessage> MidiCommandMapEditor::getKeys(CommandID cmd) {
  Array<MidiMessage> result;
  const vector<string> keys = mappings_.getKeys(static_cast<Command::Type>(cmd));
  for (vector<string>::const_iterator i = keys.begin(); i != keys.end(); ++i)
    result.add(MidiMessage(i->data(), i->size()));

  return result;
}

template <>
CommandID MidiCommandMapEditor::getCommand(const MidiMessage& key) {
  return static_cast<CommandID>(mappings_.getCommand(mappings_.toBytes(key)));
}

template <>
void MidiCommandMapEditor::removeKey(const MidiMessage& key) {
  mappings_.removeKey(mappings_.toBytes(key));
  mappings_.sendChangeMessage();
}

template <>
void MidiCommandMapEditor::addKey(CommandID cmd, const MidiMessage& key, int keyIndex) {
  mappings_.add(mappings_.toBytes(key), static_cast<Command::Type>(cmd), keyIndex);
  mappings_.sendChangeMessage();
}

template <>
void MidiCommandMapEditor::keyChosen(int result, CommandMapEditButton* button) {
  MidiCommandEntryWindow* window = dynamic_cast<MidiCommandEntryWindow*>(
      button->getCommandEntryWindow());
  if (result && button && window && window->lastKeyEntered_) {
    window->setVisible (false);
    window->owner()->setNewKey (button, window->lastKey_, false);
  }
  if (window)
    window->listen(false);

  button->setCommandEntryWindow();
}


template <>
void MidiCommandMapEditor::assignNewKeyCallback(int result,
                                                CommandMapEditButton* button,
                                                MidiMessage key) {
  if (result && button) {
    MidiCommandMapEditor* editor = dynamic_cast<MidiCommandMapEditor*>(&button->getOwner());
    editor->setNewKey (button, key, true);
  }
}

}  // namespace command
}  // namespace rec

