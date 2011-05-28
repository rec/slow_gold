#include "rec/slow/Target.h"
#include "rec/audio/Audio.h"
#include "rec/gui/Dialog.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Model.h"
#include "rec/audio/source/Player.h"
#include "rec/util/cd/Eject.h"
#include "rec/util/Math.h"

namespace rec {
namespace slow {

using rec::command::Command;
using thread::makeCallback;
using thread::functionCallback;

namespace {

// TODO: move this somewhere nicer.
void addLoopPoint(Instance* i) {
  i->components_->loops_.addLoopPoint(i->player_->getTime());
}

template <typename Operator>
void apply(Operator op, Instance* i) {
  LoopPointList loops(i->model_->loopPointList());
  (*op)(&loops);
  persist::set(loops, i->model_->file());
}

template <typename Operator>
void applyEach(Operator op, LoopPointList* loops) {
  for (int i = 0; i < loops->loop_point_size(); ++i) {
    LoopPoint* lp = loops->mutable_loop_point(i);
    lp->set_selected((*op)(lp->selected(), i));
  }
}

bool selectAll1(bool, int) { return true; }
void selectAll2(LoopPointList* lpl) { applyEach(&selectAll1, lpl); }
void selectAll(Instance* i) { apply(&selectAll2, i); }

bool selectNone1(bool, int) { return false; }
void selectNone2(LoopPointList* lpl) { applyEach(&selectNone1, lpl); }
void selectNone(Instance* i) { apply(&selectNone2, i); }

bool selectInvert1(bool s, int) { return !s; }
void selectInvert2(LoopPointList* lpl) { applyEach(&selectInvert1, lpl); }
void selectInvert(Instance* i) { apply(&selectInvert2, i); }

enum Setting {SET, RESET, TOGGLE};

struct SelectSetter {
  SelectSetter(int index, Setting s = SET) : index_(index), setting_(s) {}

  bool operator()(bool selected, int i) const {
    if (i != index_)
      return selected;
    if (i == TOGGLE)
      return !selected;
    return (setting_ == SET);
  }

  void operator()(LoopPointList* lpl) const {
    applyEach(this, lpl);
  }

  void operator()(Instance* i) const {
    apply(this, i);
  }

  int index_;
  Setting setting_;
};

Range<int> getSelection(const LoopPointList& lpl) {
  Range<int> sel;
  int size = lpl.loop_point_size();
  for (int i = 0; i < size; ++i) {
    if (lpl.loop_point(i).selected()) {
      if (!sel.size())
        sel.begin_ = i;
      sel.end_ = i + 1;
    }
  }
  return sel;
}

template <typename Op>
void selOne(Op op, LoopPointList* lpl, bool sel, bool unselOthers = false) {
  int index = mod((*op)(getSelection(*lpl)), lpl->loop_point_size());
  if (unselOthers) {
    for (int i = 0; i < lpl->loop_point_size(); ++i)
      lpl->mutable_loop_point(i)->set_selected(false);
  }
  lpl->mutable_loop_point(index)->set_selected(sel);
}

int getEnd(const Range<int>& sel) { return sel.end_; }
int preEnd(const Range<int>& sel) { return sel.end_ - 1; }
int getBegin(const Range<int>& sel) { return sel.begin_; }
int preBegin(const Range<int>& sel) { return sel.begin_ - 1; }

void extendEnd(LoopPointList* p) { selOne(&getEnd, p, true); }
void retractEnd(LoopPointList* p) { selOne(&preEnd, p, false); }
void extendBegin(LoopPointList* p) { selOne(&preBegin, p, true); }
void retractBegin(LoopPointList* p) { selOne(&getBegin, p, false); }

void selectNextOnly(LoopPointList* p) { selOne(&getEnd, p, true, true); }
void selectPreviousOnly(LoopPointList* p) { selOne(&preBegin, p, true, true); }

}  // namespace

Target::Target(Instance* i) : TargetManager(i->window_), HasInstance(i) {}

void Target::addCommands() {
  add(Command::COPY, makeCallback(&copyToClipboard),
      "Copy", "Edit",
      "Copy the current selection to the clipboard.", 'c');

  add(Command::CUT, makeCallback(&cutToClipboard),
      "Cut", "Edit",
      "Copy the current selection to the clipboard and clear the selection.", 'x');

  add(Command::DEL, makeCallback(&cutNoClipboard),
      "Delete", "Edit",
      "Delete the current selection without changing the clipboard.", 'x');

  add(Command::PASTE, makeCallback(&pasteFromClipboard),
      "Paste", "Edit",
      "Replace the current selection with a copy of the clipboard.", 'v');

  // add(Command::CLEAR_NAVIGATOR,

  add(Command::OPEN, functionCallback(&gui::dialog::openOneFile,
                                      listeners()),
      "Open...", "File",
      "Open a dialog to select a new audio file for looping.", 'o');

  add(Command::SELECT_ALL, functionCallback(selectAll, instance_),
      "Select all", "Loops",
      "Select all of the file");

  add(Command::DESELECT_ALL, functionCallback(selectNone, instance_),
      "Select none", "Loops",
      "Select none of the file");


  add(Command::CLOSE_FILE, functionCallback(persist::setter<VirtualFile>(),
                                            VirtualFile()),
      "Close", "File",
      "Close the current file", 'w');

  add(Command::EJECT_CDS, makeCallback(&cd::ejectAll),
      "Eject All", "File",
      "Eject all CDs and DVDs");

  add(Command::ADD_LOOP_POINT, functionCallback(&addLoopPoint, instance_),
      "Add Loop Point", "Transport",
      "Add a loop point at the current time.");

  add(Command::TOGGLE_START_STOP, makeCallback(player(),
      &audio::source::Player::toggle),
      "Toggle Start/Stop", "Transport",
      "Start or pause", ' ');

  using gui::audio::Loops;
  Loops* loops = &components()->loops_;

  add(Command::CLEAR_LOOPS, makeCallback(loops, &Loops::clearLoops),
      "Clear Loops", "Loop",
      "Get rid of all loop points");

  add(Command::CLEAR_SELECTION, makeCallback(loops, &Loops::clearSelection),
      "Select None", "Loop",
      "Unselect all the loop points");

  add(Command::AUDIO_PREFERENCES, makeCallback(&device()->setupPage_,
                                               &gui::audio::SetupPage::show,
                                               &components()->mainPage_),
      "Audio Preferences...", "File",
      "Open the Audio Preferences pane.", ';');

#ifdef TODO

  add(Command::CLEAR_TIME, makeCallback(&instal, &MainPage::clearTime),
      "Clear Time Stretch", "Loop",
      "Clear all time and pitch shifting");
  add(Command::TREE_CLEAR, makeCallback(cc, &ComponentContainer::clearTree),
      "Clear Workspace", "Loop",
      "Remove all files and directories from the workspace area.");
  // add(Command::FILE_CLEAR, make, &ComponentContainer::clearFile);
#endif

#ifdef TODO
  // Causes a run-time error!
  add(Command::QUIT, makeCallback(JUCEApplication::getInstance(),
                                  &JUCEApplication::systemRequestedQuit),
      "Quit", "File",
      "Quit SlowGold", 'q');
#endif

  registerAllCommandsForTarget();
}

}  // namespace slow
}  // namespace rec

