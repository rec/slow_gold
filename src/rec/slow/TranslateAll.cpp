#include "rec/slow/TranslateAll.h"
#include "rec/app/DownloadVersion.h"
#include "rec/command/map/CommandEntryWindow.h"
#include "rec/command/map/GenericCommandMapEditor.h"

namespace rec {
namespace slow {

void translateAll() {
  app::DownloadVersion::translateAll();
  command::CommandEntryWindow::translateAll();
  command::CommandMapEditorTranslation::translateAll();
}

}  // namespace slow
}  // namespace rec
