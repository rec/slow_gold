#ifndef __REC_SLOW_RECENTFILES__
#define __REC_SLOW_RECENTFILES__

#include "rec/base/base.h"
#include "rec/gui/menu/RecentFiles.pb.h"

namespace rec {

namespace music { class Metadata; }

namespace gui {

void addRecentFile(const VirtualFile&, const Message&);

class RecentFilesStrategy {
 public:
  RecentFilesStrategy() {}
  virtual ~RecentFilesStrategy() {}
  virtual string getTitle(const RecentFile&) const = 0;
  virtual string getDupeSuffix(const RecentFile&, bool isFirst) const = 0;
  virtual CommandID getRecentFileCommand() const = 0;
};

vector<string> getRecentFileNames(const RecentFilesStrategy* stategy = nullptr);

}  // namespace gui
}  // namespace rec

#endif  // __REC_SLOW_RECENTFILES__
