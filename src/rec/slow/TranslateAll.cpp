#include "rec/slow/TranslateAll.h"
#include "rec/app/DownloadVersion.h"
#include "rec/command/map/CommandEntryWindow.h"
#include "rec/command/map/GenericCommandMapEditor.h"
#include "rec/command/map/CommandMapEditButton.h"
#include "rec/command/map/CommandMapTopLevelItem.h"
#include "rec/command/map/KeyCommandMapEditor.h"

namespace rec {
namespace slow {

void translateAll() {
  app::DownloadVersion::translateAll();
  command::CommandEntryWindow::translateAll();
  command::CommandMapEditorTranslation::translateAll();
  command::CommandMapEditButton::translateAll();
  command::CommandMapTopLevelItem::translateAll();
  command::KeyCommandMapEditorTranslator::translateAll();
}

}  // namespace slow
}  // namespace rec
