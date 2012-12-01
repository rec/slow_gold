#include "rec/command/map/MidiCommandMapEditor.h"

#include "rec/audio/Device.h"
#include "rec/base/Trans.h"
#include "rec/command/Command.pb.h"
#include "rec/command/map/CommandEntryWindow.h"
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
      : CommandEntryWindow(t_WAITING, owner),
        owner_(owner),
        mappings_(mappings) {
    lastKeyEntered_ = false;
    doListen(true);
  }

  virtual void listen(bool on) { doListen(on); }
  void doListen(bool on) { mappings_->requestOneMessage(on ? this : NULL); }

  virtual ~MidiCommandEntryWindow() { listen(false); }

  virtual void operator()(const MidiMessage& msg) {
    if (msg.isNoteOn() || msg.isProgramChange() || msg.isController())
      setLastKey(toString(msg));

    mappings_->requestOneMessage(this);
  }

	MidiCommandMapEditor* owner() { return owner_; }

 private:
  MidiCommandMapEditor* owner_;
  MidiCommandMap* mappings_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(MidiCommandEntryWindow);
};

}  // namespace

const String MidiCommandMapEditor::name() const {
  return t_MIDI;
}

const String MidiCommandMapEditor::getDescription(const string& key) const {
  return midiName(midiFromString(key));
}

CommandID MidiCommandMapEditor::getCommand(const string& key) {
  return static_cast<CommandID>(mappings_->getCommand(key));
}

void MidiCommandMapEditor::removeKey(CommandID command, int keyNum) {
  mappings_->removeCommand(static_cast<Command::Type>(command), keyNum);
  mappings_->sendChangeMessage();
}

void MidiCommandMapEditor::removeKey(const string& key) {
  mappings_->removeKey(key);
  mappings_->sendChangeMessage();
}

void MidiCommandMapEditor::addKey(CommandID cmd, const string& key,
                                  int keyIndex) {
  DLOG(INFO) << "adding key " << cmd << ", " << keyIndex;
  Command::Type c = static_cast<Command::Type>(cmd);
  if (keyIndex >= 0)
    mappings_->addAtIndex(key, c, keyIndex);
  mappings_->sendChangeMessage();
}

CommandEntryWindow* MidiCommandMapEditor::newWindow() {
  return new MidiCommandEntryWindow(this, mappings_);
}

CommandMapEditor::KeyArray MidiCommandMapEditor::getKeys(CommandID c) {
  vector<string> keys(mappings_->getKeys(static_cast<Command::Type>(c)));
  KeyArray result;

  for (uint i = 0; i < keys.size(); ++i)
    result[i] = keys[i];
  return result;
}

}  // namespace command
}  // namespace rec

