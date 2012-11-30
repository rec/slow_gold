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
  MidiCommandEntryWindow(MidiCommandMapEditor* owner, MidiCommandMap* mappings)
      : CommandEntryWindow(t_WAITING),
        lastKeyEntered_(false),
        owner_(owner),
        mappings_(mappings) {
    listen(true);
  }

  void listen(bool on) { mappings_->requestOneMessage(on ? this : NULL); }

  virtual ~MidiCommandEntryWindow() { listen(false); }

  virtual void operator()(const MidiMessage& msg) {
    if (msg.isNoteOn() || msg.isProgramChange() || msg.isController()) {
      lastKey_ = msg;
      lastKeyEntered_ = true;
      thread::callAsync(this, &CommandEntryWindow::setMessage,
                        owner_->getKeyMessage(Key<MidiMessage>(msg)));
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
const String MidiCommandMapEditor::getDescription(const KeyBase& key) {
  return key.name();
}

template <>
void MidiCommandMapEditor::removeKey(CommandID command, int keyNum) {
  mappings_->removeCommand(static_cast<Command::Type>(command), keyNum);
  mappings_->sendChangeMessage();
}

template <>
bool MidiCommandMapEditor::isValid(const KeyBase&) {
  return true;
}

template <>
CommandEntryWindow* MidiCommandMapEditor::newWindow() {
  return new MidiCommandEntryWindow(this, mappings_);
}

template <>
MidiCommandMapEditor::KeyArray* MidiCommandMapEditor::getKeys(CommandID c) {
  ptr<KeyArray> result(new KeyArray);
  const vector<string> keys = mappings_->getKeys(static_cast<Command::Type>(c));
  for (vector<string>::const_iterator i = keys.begin(); i != keys.end(); ++i)
    result->add(makeKey(MidiMessage(i->data(), i->size())));

  return result.transfer();
}

template <>
CommandID MidiCommandMapEditor::getCommand(const KeyBase& key) {
  return static_cast<CommandID>(mappings_->getCommand(toBytes(key)));
}

template <>
void MidiCommandMapEditor::removeKey(const KeyBase& key) {
  mappings_->removeKey(toBytes(key));
  mappings_->sendChangeMessage();
}

template <>
void MidiCommandMapEditor::addKey(CommandID cmd, const KeyBase& key,
                                  int keyIndex) {
  Command::Type c = static_cast<Command::Type>(cmd);
  if (keyIndex >= 0)
    mappings_->addAtIndex(toBytes(key), c, keyIndex);
  mappings_->sendChangeMessage();
}

template <>
void MidiCommandMapEditor::keyChosen(int result, CommandMapEditButton* button) {
  MidiCommandEntryWindow* window = dynamic_cast<MidiCommandEntryWindow*>(
      button->getCommandEntryWindow());
  if (result && button && window && window->lastKeyEntered_) {
    window->setVisible (false);
    window->owner()->setNewKey(button, Key<MidiMessage>(window->lastKey_), false);
  }
  if (window)
    window->listen(false);

  button->setCommandEntryWindow();
}


template <>
void MidiCommandMapEditor::assignNewKeyCallback(int result,
                                                CommandMapEditButton* button,
                                                const KeyBase* key) {
  if (result && button) {
    MidiCommandMapEditor* editor = dynamic_cast<MidiCommandMapEditor*>(&button->getOwner());
    editor->setNewKey(button, *key, true);
  }
}

}  // namespace command
}  // namespace rec

