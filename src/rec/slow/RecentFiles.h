#ifndef __REC_SLOW_RECENTFILES__
#define __REC_SLOW_RECENTFILES__

#include "rec/base/basictypes.h"
#include "rec/slow/RecentFiles.pb.h"

namespace rec {
namespace slow {

RecentFiles getSortedRecentFiles();

void addRecentFile(const std::string& filename);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_RECENTFILES__
