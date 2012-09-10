#include "rec/slow/callbacks/RepeatedCallbacks.h"

#include "rec/audio/AudioSettings.pb.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/RecentFiles.pb.h"
#include "rec/slow/callbacks/CallbackUtils.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/LoopSnapshot.h"
#include "rec/slow/Menus.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/util/LoopPoint.h"

using namespace std;
using namespace rec::command;

namespace rec {
namespace slow {

namespace {

// Skin

using namespace rec::widget::waveform;

const RealTime MAX_JUMP_TIME = 1.0;

void setTimeFromSegment(LoopSnapshot* snapshot, int segment) {
  Viewport viewport = data::getProto<Viewport>(snapshot->instance_->file());
  snapshot->viewport_.CopyFrom(viewport);
  snapshot->loops_ = snapshot->viewport_.mutable_loop_points();  // TODO: hacky!
  SampleTime time = snapshot->loops_->loop_point(segment).time();
  snapshot->instance_->currentTime_->jumpToTime(time);
}

void jump(LoopSnapshot* snap, CommandIDEncoder pos) {
  SampleTime time = snap->instance_->time();

  int size = snap->loops_->loop_point_size();
  int segment = audio::getSegment(*snap->loops_, time);
  int p = pos.toIndex(segment, size);

  // Special case for "jump back";
  if (pos == command::CommandIDEncoder::PREVIOUS &&
      (time - snap->loops_->loop_point(segment).time()) >=
      SampleTime(MAX_JUMP_TIME, snap->loops_->sample_rate())) {
    p = segment;
  }

  setTimeFromSegment(snap, p);
  snap->loops_->mutable_loop_point(p)->set_selected(true);
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
static const int RECENT_MENU_REPEATS = 32;
static const int RECENT_FILE_THREAD_PRIORITY = 4;

void loadRecentFile(Instance* instance, int i) {
  gui::RecentFiles rf = data::getProto<gui::RecentFiles>();
  if (i < 0 || i >= rf.file_size()) {
    LOG(DFATAL) << "Can't load recent, i=" << i << ", size=" << rf.file_size();
    return;
  }

  thread::runInNewThread("loadRecentFile", RECENT_FILE_THREAD_PRIORITY,
                         instance->currentFile_.get(),
                         &CurrentFile::setVirtualFile,
                         rf.file(i).file(), true);
}

void setSaveFileType(Instance* instance, int i) {
  using audio::AudioSettings;

  AudioSettings settings = data::getProto<AudioSettings>();
  settings.set_file_type_for_save(static_cast<AudioSettings::FileType>(i));
  data::setProto(settings);
  instance->menus_->menuItemsChanged();
}

void setLanguage(Instance* instance, int i) {
  app::AppSettings inter = data::getProto<app::AppSettings>();
  inter.set_language(static_cast<Language>(i));
  data::setProto(inter);
  instance->menus_->menuItemsChanged();
}

void openPreviousFile(Instance* i) {
  gui::RecentFiles rf = data::getProto<gui::RecentFiles>();
  int size = rf.file_size();
  if (size) {
    if (data::equals(rf.file(0).file(), i->file())) {
      if (size > 1)
        loadRecentFile(i, 1);
    } else {
      loadRecentFile(i, 0);
    }
  }
}

void jumpSelected(LoopSnapshot* snap, CommandIDEncoder pos) {
  vector<int> selected;
  const LoopPointList& loops = *snap->loops_;
  size_t s = 0;
  bool found = false;
  int selectedSegment = audio::getSegment(loops, snap->instance_->time());

  for (int i = 0; i < loops.loop_point_size(); ++i) {
    if (!audio::getSelectionCount(loops) || loops.loop_point(i).selected()) {
      if (i == selectedSegment) {
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

void nudgeWithinSegment(Instance* i, const LoopPointList& selection, bool inc) {
  SampleTime begin = selection.loop_point(0).time();
  SampleTime end = selection.length();
  SampleTime width = end - begin;
  SampleRate rate = i->getSourceSampleRate();
  SampleTime nudge(data::getProto<audio::AudioSettings>().time_nudge(), rate);
  nudge = std::min(nudge, SampleTime(width / 2));
  SampleTime time = i->time() + (inc ? nudge : - nudge);
  while (time < begin)
    time += width;

  while (time >= end)
    time -= width;
  i->currentTime_->jumpToTime(time);
}

void nudgeTime(Instance* i, bool inc) {
  LoopSnapshot s(i);
  LoopPointList selection = audio::getSelected(*s.loops_, true);
  if (!selection.loop_point_size())
    selection = audio::getSelected(*s.loops_, false);
  if (selection.loop_point_size() == 1)
    nudgeWithinSegment(i, selection, inc);
  else
    jumpSelected(&s, inc ? CommandIDEncoder::NEXT : CommandIDEncoder::PREVIOUS);
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

  for (int j = 0; j < audio::AudioSettings::COUNT; ++j) {
    CommandID id = CommandIDEncoder::toCommandID(j, Command::SET_SAVE_FORMAT);
    addCallback(t, id, setSaveFileType, i, j);
  }

  for (int j = 0; j <= app::AppSettings::LAST; ++j) {
    CommandID id = CommandIDEncoder::toCommandID(j, Command::SET_LANGUAGE);
    addCallback(t, id, setLanguage, i, j);
  }


  addCallback(t, Command::OPEN_PREVIOUS_FILE, openPreviousFile, i);

  addCallback(t, Command::NUDGE_BACKWARD, nudgeTime, i, false);
  addCallback(t, Command::NUDGE_FORWARD, nudgeTime, i, true);
}

}  // namespace slow
}  // namespace rec
