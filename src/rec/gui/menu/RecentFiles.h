#ifndef __REC_SLOW_RECENTFILES__
#define __REC_SLOW_RECENTFILES__

#include "rec/base/base.h"
#include "rec/gui/menu/RecentFiles.pb.h"

namespace rec {

namespace music { class Metadata; }

namespace gui {

void addRecentFile(const VirtualFile&, const Message&);

typedef string (*TitleGetter)(const RecentFile&);
string getMusicTitle(const RecentFile&);

typedef string (*DupeSuffixGetter)(const RecentFile&, bool isFirst);
string getMusicDupeSuffix(const RecentFile&, bool isFirst);

vector<string> getRecentFileNames(
    TitleGetter titleGetter = getMusicTitle,
    DupeSuffixGetter dupeSuffixGetter = getMusicDupeSuffix);

}  // namespace gui
}  // namespace rec

#endif  // __REC_SLOW_RECENTFILES__
