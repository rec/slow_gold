#ifndef __REC_SLOW_DOWNLOADVERSION__
#define __REC_SLOW_DOWNLOADVERSION__

#include "rec/base/base.h"

namespace rec {
namespace app {

enum DownloadStatus {
  DOWNLOAD_NOT_FOUND,
  DOWNLOAD_SUCCEEDED,
  DOWNLOAD_CANCELLED_OR_FAILED
};

// Returns true if a new version was downloaded.
void downloadNewVersionIfNeeded(const String& version, const String& name);
bool downloadNewVersionIfNeededBlocking();

}  // namespace app
}  // namespace rec

#endif  // __REC_SLOW_DOWNLOADVERSION__
