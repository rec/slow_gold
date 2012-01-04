#include "rec/slow/Menus.h"
#include "rec/base/ArraySize.h"
#include "rec/gui/RecentFiles.h"
#include "rec/util/Undo.h"
#include "rec/slow/Instance.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/slow/Target.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/util/Cuttable.h"

using namespace rec::command;

namespace rec {
namespace slow {

static const int SLOT_COUNT = 10;

Menus::Menus(Instance* i) : HasInstance(i), isAdvanced_(false) {}

void Menus::operator()(const GuiSettings& settings) {
  //  isAdvanced_ = settings.advanced_menus();
}

const StringArray Menus::getMenuBarNames() {
  static const char* NAMES[] = {"File", "Edit", "Audio", "Transport", "Select",
                                "Display"};
  return StringArray(NAMES, arraysize(NAMES));
}

namespace {

class ManagerAndMenu {
 public:
  ManagerAndMenu(TargetManager* t, bool isAdvanced = false)
      : targetManager_(t), isAdvanced_(isAdvanced) {
  }

  const PopupMenu makeMenu(const String& name) {
    menu_.clear();
    addMenu(name);
    return menu_;
  }

 private:
  void add(CommandID id,
           const String& name = String::empty,
           bool enabled = true,
           PopupMenu* m = NULL) {
    targetManager_->addCommandItem(m ? m : &menu_, id, enabled, name);
  }

  void addRepeat(Command::Type command,
                 int slot,
                 const String& name = String::empty,
                 bool enabled = true,
                 PopupMenu* m = NULL) {
    add(CommandIDEncoder::toCommandID(slot, command), name, enabled, m);
  }

  void addEnabled(Command::Type command, bool enabled) {
    add(command, "", enabled);
  }

  void addBank(Command::Type command, const String& name,
               int begin = CommandIDEncoder::FIRST,
               int end = SLOT_COUNT) {
    PopupMenu sub;
    for (int i = begin; i < end; ++i) {
      if (i == 0)
        sub.addSeparator();
      addRepeat(command, i, "", true, &sub);
    }

    menu_.addSubMenu(name, sub);
  }

  void addFileMenu() {
    add(Command::OPEN);
    add(Command::CLOSE_FILE);
    add(Command::EJECT_CDS);

    menu_.addSeparator();

    // add(Command::CLEAR_NAVIGATOR);
    add(Command::KEYBOARD_MAPPINGS);
    add(Command::MIDI_MAPPINGS);

    std::vector<string> recent = rec::gui::getRecentFileNames();
    PopupMenu submenu;
    for (uint i = 0; i < recent.size(); ++i)
      addRepeat(Command::RECENT_FILES, i, str(recent[i]), true, &submenu);

    menu_.addSubMenu("Open recent", submenu);

  #if !JUCE_MAC
    add(Command::ABOUT_THIS_PROGRAM);
    add(Command::QUIT);
  #endif
  }

  void addEditMenu() {
    addEnabled(Command::UNDO, canUndo());
    addEnabled(Command::REDO, canRedo());

    menu_.addSeparator();

    addEnabled(Command::CUT, canCut());
    addEnabled(Command::COPY, canCopy());
    addEnabled(Command::PASTE, canPaste());
  }

  void addAudioMenu() {
    add(Command::MUTE_VOLUME_TOGGLE);
    add(Command::DIM_VOLUME_TOGGLE);
    add(Command::NUDGE_VOLUME_UP);
    add(Command::NUDGE_VOLUME_DOWN);
    add(Command::RESET_GAIN_TO_UNITY);
    add(Command::TOGGLE_STRETCH_ENABLE);

    menu_.addSeparator();

    add(Command::AUDIO_PREFERENCES);
  }

  void addSelectMenu() {
    add(Command::SELECT_ALL);
    add(Command::DESELECT_ALL);
    add(Command::INVERT_LOOP_SELECTION);
    add(Command::TOGGLE_WHOLE_SONG_LOOP);

    menu_.addSeparator();

    addBank(Command::SELECT, "Select...");
    addBank(Command::SELECT_ONLY, "Select Only...");
    addBank(Command::TOGGLE_SELECTION, "Toggle...");
    addBank(Command::UNSELECT, "Unselect...");
  }

  void addTransportMenu() {
    add(Command::TOGGLE_START_STOP);
    add(Command::ADD_LOOP_POINT);
    add(Command::CLEAR_LOOPS);
    add(Command::TOGGLE_PREFADER_LEVELS);

    menu_.addSeparator();

    addBank(Command::JUMP, "Jump To...");
    addBank(Command::JUMP_SELECTED, "Jump To Selected...");
  }

  void addDisplayMenu() {
    add(Command::TOGGLE_GRID_DISPLAY);
    add(Command::TOGGLE_PARALLEL_WAVEFORMS);
    add(Command::TOGGLE_FOLLOW_CURSOR);
    add(Command::TOGGLE_SHOW_HELP_PANE);
    add(Command::TOGGLE_SHOW_TOOLTIPS);
    add(Command::TOGGLE_SHOW_SELECTION_BUTTONS);
    add(Command::TOGGLE_SHOW_CURSOR_LABELS);
    add(Command::TOGGLE_SHOW_TIMES_AT_TOP);
    add(Command::TOGGLE_SHOW_LABELS_AT_TOP);
    add(Command::TOGGLE_COMMAND_BAR_AT_LEFT);
    add(Command::TOGGLE_COMMAND_BAR_AT_TOP);
    add(Command::TOGGLE_MODES_AT_LEFT);
    add(Command::TOGGLE_MODES_AT_TOP);
  }

  void addMenu(const String& menuName) {
    if (menuName == "File")
      addFileMenu();

    else if (menuName == "Edit")
      addEditMenu();

    else if (menuName == "Audio")
      addAudioMenu();

    else if (menuName == "Select")
      addSelectMenu();

    else if (menuName == "Transport")
      addTransportMenu();

    else if (menuName == "Display")
      addDisplayMenu();
  }

 private:
  TargetManager* targetManager_;
  PopupMenu menu_;
  bool isAdvanced_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(ManagerAndMenu);
};

}  // namespace

const PopupMenu Menus::getMenuForIndex(int menuIndex, const String& menuName) {
  return ManagerAndMenu(target()->targetManager()).makeMenu(menuName);
}

}  // namespace slow
}  // namespace rec

