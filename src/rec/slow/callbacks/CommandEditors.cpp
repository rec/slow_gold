#include "rec/slow/callbacks/CommandEditors.h"

#include "rec/base/Trans.h"

#include "rec/command/KeyboardBindings.h"
#include "rec/command/map/KeyCommandMapEditor.h"
#include "rec/command/map/MidiCommandMapEditor.h"
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

bool displayEditorWindow(command::CommandMapEditor* comp,
                         const String& title) {
  gui::DialogLocker l;
  if (!l.isLocked()) {
    beep();
    return false;
  }

  comp->initialize();
  comp->setBounds(0, 0, EDITOR_WIDTH, EDITOR_HEIGHT);

  l.setModalComponent(comp);
  juce::DialogWindow::showModalDialog(title, comp, NULL, juce::Colours::white,
                                      true, true, true);
  return true;
}

}  // namespace

void clearKeyboardMappings() {
  if (AlertWindow::showOkCancelBox(AlertWindow::InfoIcon,
                                   t_CLEAR_KEYBOARD_MAPPINGS_TITLE,
                                   t_CLEAR_KEYBOARD_MAPPINGS_FULL,
                                   t_OK, t_CANCEL)) {
    Instance* i = Instance::getInstance();
    command::clearKeyboardBindings(*i->commandRecordTable_,
                                   &i->applicationCommandManager_);

  }
}


void clearMidiMappings() {
  if (AlertWindow::showOkCancelBox(AlertWindow::InfoIcon,
                                   t_CLEAR_MIDI_MAPPINGS_TITLE,
                                   t_CLEAR_MIDI_MAPPINGS_FULL,
                                   t_OK, t_CANCEL)) {
    data::setProto(command::CommandMapProto());
  }
}

void keyboardMappings() {
  Instance* i = Instance::getInstance();
  ApplicationCommandManager* manager = &i->applicationCommandManager_;
  command::KeyCommandMapEditor comp(manager, manager->getKeyMappings());
  if (displayEditorWindow(&comp, t_KEYBOARD_EDITOR_TITLE))
    command::saveKeyboardBindings(manager);
}

void midiMappings() {
  Instance* i = Instance::getInstance();
  ApplicationCommandManager* manager = &i->applicationCommandManager_;
  command::MidiCommandMapEditor comp(manager, i->midiCommandMap_.get());
  if (displayEditorWindow(&comp, t_MIDI_EDITOR_TITLE))
    data::setProto(i->midiCommandMap_->getProto(), data::global());
}

}  // namespace slow
}  // namespace rec