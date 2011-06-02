#include "rec/slow/TargetCommands.h"
#include "rec/audio/Audio.h"
#include "rec/data/persist/Persist.h"
#include "rec/gui/Dialog.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Model.h"
#include "rec/slow/Selections.h"
#include "rec/slow/Target.h"
#include "rec/audio/source/Player.h"
#include "rec/util/cd/Eject.h"
#include "rec/util/Math.h"
#include "rec/util/thread/FunctionCallback.h"

namespace rec {
namespace slow {

void clearNavigator() { persist::set(VirtualFileList()); }

void jumpToLoopPoint(Instance* i, int offset) {
  LoopPointList loops(i->model_->loopPointList());
  SampleTime time = i->player_->getNextReadPosition();
  int j = 0, size = loops.loop_point_size();
  for (; j < size && time >= loops.loop_point(j).time(); ++j);
  j += offset;
  if (j >= size)
    j = 0;
  else if (j < 0)
    j = size - 1;
  SampleTime pos = audio::timeToSamples(loops.loop_point(j).time());
  i->model_->jumpToSamplePosition(pos);
}

void jumpToStart(Instance* i) {
 i->model_->jumpToSamplePosition(i->model_->timeSelection().begin()->first);
}

void keyboardMappings(Instance* i) {
  gui::DialogLocker l;
  if (!l.isLocked())
    return;  // TODO beep

  juce::KeyMappingEditorComponent comp(
      *i->target_->commandManager()->getKeyMappings(), true);

  comp.setBounds(0, 0, 1000, 1000);

  int res = juce::DialogWindow::showModalDialog("Select keyboard mappings",
                                                &comp, NULL, juce::Colours::white,
                                                true, true, true);
}

void nudgeBeginLeft(Instance* i) {
}

void nudgeBeginRight(Instance* i) {
}

void nudgeEndLeft(Instance* i) {
}

void nudgeEndRight(Instance* i) {
}

void nudgeVolumeDown(Instance* i) {
}

void nudgeVolumeUp(Instance* i) {
}

void recentFiles(Instance* i) {
}

void toggleWholeSongLoop(Instance* i) {
}

void toggleStartStop(Instance* i) {
}

void toggleStretchEnable(Instance* i) {
}

void treeClose(Instance* i) {
}

void treeDown(Instance* i) {
}

void treeLeft(Instance* i) {
}

void treeOpen(Instance* i) {
}

void treeRight(Instance* i) {
}

void treeUp(Instance* i) {
}

void zoomIn(Instance* i) {
}

void zoomOut(Instance* i) {
}

}  // namespace slow
}  // namespace rec
