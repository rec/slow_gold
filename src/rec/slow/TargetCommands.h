#ifndef __REC_SLOW_TARGETCOMMANDS__
#define __REC_SLOW_TARGETCOMMANDS__

#include "rec/base/base.h"

namespace rec {
namespace slow {

class Instance;

void clearNavigator();
void dimVolumeToggle(Instance*);
void keyboardMappings(Instance*);
void midiMappings(Instance*);
void muteVolumeToggle(Instance*);
void nudgeBeginLeft(Instance*);
void nudgeBeginRight(Instance*);
void nudgeEndLeft(Instance*);
void nudgeEndRight(Instance*);
void nudgeVolumeDown(Instance*);
void nudgeVolumeUp(Instance*);
void recentFiles(Instance*);
void resetGainToUnity(Instance*);
void toggleWholeSongLoop(Instance*);
void toggleStretchEnable(Instance*);
void treeClose(Instance*);
void treeDown(Instance*);
void treeLeft(Instance*);
void treeOpen(Instance*);
void treeRight(Instance*);
void treeUp(Instance*);
void zoomIn(Instance*);
void zoomOut(Instance*);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_TARGETCOMMANDS__
