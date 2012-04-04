#include "rec/slow/TranslateAll.h"
#include "rec/app/DownloadVersion.h"
#include "rec/command/map/CommandEntryWindow.h"

namespace rec {
namespace slow {

void translateAll() {
  app::DownloadVersion::translateAll();
  command::CommandEntryWindow::translateAll();
}

}  // namespace slow
}  // namespace rec
