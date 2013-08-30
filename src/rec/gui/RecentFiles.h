#ifndef __REC_SLOW_RECENTFILES__
#define __REC_SLOW_RECENTFILES__

#include "rec/base/base.h"
#include "rec/gui/RecentFiles.pb.h"

namespace rec {

namespace music { class Metadata; }

namespace gui {

void addRecentFile(const VirtualFile&, const Message&);

typedef string (*TitleGetter)(const RecentFile&);
string getMusicTitle(const RecentFile&);

vector<string> getRecentFileNames(TitleGetter titleGetter = getMusicTitle);

}  // namespace gui
}  // namespace rec

#endif  // __REC_SLOW_RECENTFILES__
