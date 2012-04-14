#ifndef __REC_SLOW_CALLBACKS_SAVEFILE__
#define __REC_SLOW_CALLBACKS_SAVEFILE__

#include "rec/base/base.h"

namespace rec {
namespace slow {

class Instance;

void saveFile(Instance* instance, const String& suffix, bool useSelection);

inline void saveAsAIFF(Instance* i) { saveFile(i, ".aiff", false); }
inline void saveAsFLAC(Instance* i) { saveFile(i, ".flac", false); }
inline void saveAsMP3(Instance* i) { saveFile(i, ".mp3", false); }
inline void saveAsOGG(Instance* i) { saveFile(i, ".ogg", false); }
inline void saveAsWAV(Instance* i) { saveFile(i, ".wav", false); }

inline void saveSelectionAsAIFF(Instance* i) { saveFile(i, ".aiff", true); }
inline void saveSelectionAsFLAC(Instance* i) { saveFile(i, ".flac", true); }
inline void saveSelectionAsMP3(Instance* i) { saveFile(i, ".mp3", true); }
inline void saveSelectionAsOGG(Instance* i) { saveFile(i, ".ogg", true); }
inline void saveSelectionAsWAV(Instance* i) { saveFile(i, ".wav", true); }

struct SaveFile {
  static void translateAll();
};


}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_CALLBACKS_SAVEFILE__
