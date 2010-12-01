#ifndef __REC_SLOW_RECENTFILES__
#define __REC_SLOW_RECENTFILES__

#include "rec/base/base.h"
#include "rec/gui/RecentFiles.pb.h"
#include "rec/widget/tree/VolumeFile.pb.h"

namespace rec {
namespace gui {

RecentFiles getSortedRecentFiles();

void addRecentFile(const widget::tree::VolumeFile& filename);

}  // namespace gui
}  // namespace rec

#endif  // __REC_SLOW_RECENTFILES__
