#ifndef __REC_SLOW_TARGETCOMMANDS__
#define __REC_SLOW_TARGETCOMMANDS__

#include "rec/base/base.h"

namespace rec {
namespace slow {

class Instance;

void clearNavigator();
void jumpToLoopPoint(Instance* i, int offset);
void jumpToStart(Instance* i);
void keyboardMappings(Instance* i);
void nudgeBeginLeft(Instance* i);
void nudgeBeginRight(Instance* i);
void nudgeEndLeft(Instance* i);
void nudgeEndRight(Instance* i);
void nudgeVolumeDown(Instance* i);
void nudgeVolumeUp(Instance* i);
void recentFiles(Instance* i);
void toggleWholeSongLoop(Instance* i);
void toggleStartStop(Instance* i);
void toggleStretchEnable(Instance* i);
void treeClose(Instance* i);
void treeDown(Instance* i);
void treeLeft(Instance* i);
void treeOpen(Instance* i);
void treeRight(Instance* i);
void treeUp(Instance* i);
void zoomIn(Instance* i);
void zoomOut(Instance* i);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_TARGETCOMMANDS__
