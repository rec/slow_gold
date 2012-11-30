#include "rec/command/map/MidiCommandMapEditor.h"

#include "rec/audio/Device.h"
#include "rec/base/Trans.h"
#include "rec/command/Command.pb.h"
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
  MidiCommandEntryWindow(MidiCommandMapEditorBase* owner, MidiCommandMap* mappings)
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
                        owner_->getKeyMessage(toString(msg)));
    }

    mappings_->requestOneMessage(this);
  }

	MidiCommandMapEditorBase* owner() { return owner_; }
  MidiMessage lastKey_;
  bool lastKeyEntered_;

 private:
  MidiCommandMapEditorBase* owner_;
  MidiCommandMap* mappings_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(MidiCommandEntryWindow);
};

}  // namespace

template <>
const String MidiCommandMapEditorBase::name() {
  return t_MIDI;
}

template <>
const String MidiCommandMapEditorBase::getDescription(const string& key) {
  return midiName(midiFromString(key));
}

template <>
void MidiCommandMapEditorBase::removeKey(CommandID command, int keyNum) {
  mappings_->removeCommand(static_cast<Command::Type>(command), keyNum);
  mappings_->sendChangeMessage();
}

template <>
bool MidiCommandMapEditorBase::isValid(const string&) {
  return true;
}

template <>
CommandEntryWindow* MidiCommandMapEditorBase::newWindow() {
  return new MidiCommandEntryWindow(this, mappings_);
}

template <>
MidiCommandMapEditorBase::KeyArray MidiCommandMapEditorBase::getKeys(CommandID c) {
  vector<string> keys(mappings_->getKeys(static_cast<Command::Type>(c)));
  KeyArray result;

  for (uint i = 0; i < keys.size(); ++i)
    result[i] = keys[i];
  return result;
}

template <>
CommandID MidiCommandMapEditorBase::getCommand(const string& key) {
  return static_cast<CommandID>(mappings_->getCommand(key));
}

template <>
void MidiCommandMapEditorBase::removeKey(const string& key) {
  mappings_->removeKey(key);
  mappings_->sendChangeMessage();
}

template <>
void MidiCommandMapEditorBase::addKey(CommandID cmd, const string& key,
                                  int keyIndex) {
  DLOG(INFO) << "adding key " << cmd << ", " << keyIndex;
  Command::Type c = static_cast<Command::Type>(cmd);
  if (keyIndex >= 0)
    mappings_->addAtIndex(key, c, keyIndex);
  mappings_->sendChangeMessage();
}

template <>
void MidiCommandMapEditorBase::keyChosen(int result, CommandMapEditButton* button) {
  MidiCommandEntryWindow* window = dynamic_cast<MidiCommandEntryWindow*>(
      button->getCommandEntryWindow());
  if (result && button && window && window->lastKeyEntered_) {
    window->setVisible (false);
    window->owner()->setNewKey(button, toString(window->lastKey_), false);
  }
  if (window)
    window->listen(false);

  button->setCommandEntryWindow();
}


template <>
void MidiCommandMapEditorBase::assignNewKeyCallback(int result,
                                                CommandMapEditButton* button,
                                                const string* key) {
  if (result && button) {
    MidiCommandMapEditorBase* editor = dynamic_cast<MidiCommandMapEditorBase*>(&button->getOwner());
    editor->setNewKey(button, *key, true);
  }
}

}  // namespace command
}  // namespace rec

