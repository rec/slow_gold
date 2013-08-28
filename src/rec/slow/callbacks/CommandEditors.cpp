#include "rec/slow/callbacks/CommandEditors.h"

#include "rec/base/Trans.h"

#include "rec/command/KeyboardBindings.h"
#include "rec/command/map/CommandMap.pb.h"
#include "rec/command/map/KeyStrokeEditor.h"
#include "rec/command/map/MidiEditor.h"
#include "rec/gui/Dialog.h"
#include "rec/slow/Instance.h"

TRAN(CLEAR_KEYBOARD_MAPPINGS_TITLE, "Clear Keyboard Mappings.");
TRAN(CLEAR_KEYBOARD_MAPPINGS_FULL, "Clear all keyboard mappings to factory "
                                   "default?");
TRAN(CLEAR_MIDI_MAPPINGS_TITLE, "Clear MIDI Mappings.");
TRAN(CLEAR_MIDI_MAPPINGS_FULL, "Clear all MIDI mappings?");

TRAN(KEYBOARD_EDITOR_TITLE, "Attach Commands To Keystrokes");
TRAN(MIDI_EDITOR_TITLE, "Attach Commands To MIDI events");

namespace rec {
namespace slow {

namespace {

const int EDITOR_WIDTH = 500;
const int EDITOR_HEIGHT = 800;

bool displayEditorWindow(command::Editor* editor,
                         const String& title) {
  gui::DialogLocker l;
  if (!l.isLocked()) {
    beep();
    return false;
  }

  editor->initialize();
  editor->setBounds(0, 0, EDITOR_WIDTH, EDITOR_HEIGHT);

  l.setModalComponent(editor);
  juce::DialogWindow::showModalDialog(title, editor, nullptr, juce::Colours::white,
                                      true, true, true);
  return editor->wasChanged();
}

}  // namespace

void clearKeyboardMappings() {
  if (AlertWindow::showOkCancelBox(AlertWindow::InfoIcon,
                                   t_CLEAR_KEYBOARD_MAPPINGS_TITLE,
                                   t_CLEAR_KEYBOARD_MAPPINGS_FULL,
                                   t_OK, t_CANCEL)) {
    // TODO
#if 0
    Instance* i = Instance::getInstance();
    command::clearKeyboardBindings(*i->commandRecordTable_,
                                   &i->applicationCommandManager_);
#endif
  }
}

void clearMidiMappings() {
  if (AlertWindow::showOkCancelBox(AlertWindow::InfoIcon,
                                   t_CLEAR_MIDI_MAPPINGS_TITLE,
                                   t_CLEAR_MIDI_MAPPINGS_FULL,
                                   t_OK, t_CANCEL)) {
    data::setProto(command::MidiCommandMapProto(), data::global());
  }
}

using namespace rec::data;
using namespace rec::command;

void keyboardMappings() {
  Instance* i = Instance::getInstance();
  ApplicationCommandManager* manager = &i->applicationCommandManager_;
  CommandMap commandMap;
  commandMap.addCommands(getKeyboardBindings());

  command::KeyStrokeEditor comp(manager, &commandMap);
  if (displayEditorWindow(&comp, t_KEYBOARD_EDITOR_TITLE)) {
    KeyStrokeCommandMapProto map;
    *(map.mutable_map()) = commandMap.getProto();
    setProto(map, global());
    command::loadKeyboardBindings(manager);
  }
}

void midiMappings() {
  Instance* i = Instance::getInstance();
  ApplicationCommandManager* manager = &i->applicationCommandManager_;
  command::MidiEditor comp(manager, i->midiCommandMap_.get());
  if (displayEditorWindow(&comp, t_MIDI_EDITOR_TITLE))
    data::setProto(i->midiCommandMap_->getProto(), data::global());
}

}  // namespace slow
}  // namespace rec
