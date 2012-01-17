#include "rec/slow/callbacks/RepeatedCallbacks.h"
#include "rec/gui/RecentFiles.pb.h"
#include "rec/slow/callbacks/CallbackUtils.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/BufferFiller.h"
#include "rec/util/thread/MakeThread.h"

using namespace std;
using namespace rec::command;

namespace rec {
namespace slow {

namespace {

int getSegment(const LoopSnapshot& snap) {
  return audio::getSegment(snap.loops_, snap.instance_->time());
}

void setTimeFromSegment(LoopSnapshot* snapshot, int segment) {
  Samples<44100> time = snapshot->loops_.loop_point(segment).time();
  snapshot->instance_->currentTime_->jumpToTime(time);
}

void jump(LoopSnapshot* snap, CommandIDEncoder pos) {
  int size = snap->loops_.loop_point_size();
  int segment = getSegment(*snap);
  int p = pos.toIndex(segment, size);
  snap->loops_.mutable_loop_point(p)->set_selected(true);
  setTimeFromSegment(snap, p);
}

void jumpSelected(LoopSnapshot* snap, CommandIDEncoder pos) {
  vector<int> selected;
  const LoopPointList& loops = snap->loops_;
  size_t s = 0;
  bool found = false;
  for (int i = 0; i < loops.loop_point_size(); ++i) {
    if (!audio::getSelectionCount(loops) || loops.loop_point(i).selected()) {
      if (i == getSegment(*snap)) {
        DCHECK(!found);
        s = selected.size();
        found = true;
      }
      selected.push_back(i);
    }
  }
  int segment = 0;
  if (found)
    segment = selected[pos.toIndex(s, selected.size())];
  else if (!selected.empty())
    segment = selected[0];

  setTimeFromSegment(snap, segment);
}

bool selectAdd(int index, int pos, bool sel, bool) { return sel || index == pos; }
bool selectOnly(int index, int pos, bool, bool) { return index == pos; }
bool toggle(int index, int pos, bool sel, bool) { return sel != (index == pos); }
bool unselect(int index, int pos, bool sel, bool) { return sel && index != pos; }

void addCallback(CommandRecordTable* c, int32 type, CommandIDEncoder position,
         SelectorFunction f, Instance* i) {
  addCallback(c, position.toCommandID(type), select, i, f, position);
}

void addCallback(CommandRecordTable* c, int32 type, CommandIDEncoder position,
         LoopSnapshotFunction f, Instance* i) {
  addCallback(c, position.toCommandID(type), loop, i, f, position);
}

// TODO: this duplicates a value in the Repeated.def data file.
static const int RECENT_MENU_REPEATS = 10;
static const int RECENT_FILE_THREAD_PRIORITY = 4;

void loadRecentFile(Instance* instance, int i) {
  gui::RecentFiles rf = data::getGlobal<gui::RecentFiles>();
  if (i < 0 || i >= rf.file_size()) {
    LOG(DFATAL) << "Can't load recent, i=" << i << ", size=" << rf.file_size();
    return;
  }

  thread::runInNewThread("loadRecentFile", RECENT_FILE_THREAD_PRIORITY,
                         instance->currentFile_.get(),
                         &CurrentFile::setFileAndData,
                         rf.file(i).file());
}

}  // namespace

void addRepeatedCallbacks(CommandRecordTable* t, Instance* i, int repeat) {
  for (int j = CommandIDEncoder::FIRST; j < repeat; ++j) {
  	CommandIDEncoder pos(j);
    addCallback(t, Command::SELECT, pos, selectAdd, i);
    addCallback(t, Command::SELECT_ONLY, pos, selectOnly, i);
    addCallback(t, Command::TOGGLE_SELECTION, pos, toggle, i);
    addCallback(t, Command::UNSELECT, pos, unselect, i);

    addCallback(t, Command::JUMP_SELECTED, pos, jumpSelected, i);
    addCallback(t, Command::JUMP, pos, jump, i);
  }

  for (int j = 0; j < RECENT_MENU_REPEATS; ++j) {
    CommandID id = CommandIDEncoder::toCommandID(j, Command::RECENT_FILES);
    addCallback(t, id, loadRecentFile, i, j);
  }
}

}  // namespace slow
}  // namespace rec
