#include "rec/slow/TranslateAll.h"
#include "rec/app/DownloadVersion.h"
#include "rec/command/map/CommandEntryWindow.h"
#include "rec/command/map/GenericCommandMapEditor.h"
#include "rec/command/map/CommandMapEditButton.h"
#include "rec/command/map/CommandMapTopLevelItem.h"
#include "rec/command/map/CommandMapEditor.h"
#include "rec/command/map/KeyCommandMapEditor.h"
#include "rec/command/map/MidiCommandMapEditor.h"
#include "rec/command/map/MidiName.h"
#include "rec/gui/audio/SetupPage.h"
#include "rec/music/CreateMusicFileReader.h"
#include "rec/slow/AboutWindow.h"
#include "rec/slow/callbacks/InstanceCallbacks.h"
#include "rec/slow/callbacks/GlobalCallbacks.h"
#include "rec/slow/callbacks/SaveFile.h"
#include "rec/util/cd/CDReader.h"
#include "rec/widget/tree/CD.h"
#include "rec/widget/tree/TreeViewDropAll.h"

namespace rec {
namespace slow {

void translateAll() {
  AboutWindow::translateAll();
  GlobalCallbacks::translateAll();
  InstanceCallbacks::translateAll();
  SaveFile::translateAll();

  app::DownloadVersion::translateAll();

  command::CommandEntryWindow::translateAll();
  command::CommandMapEditButton::translateAll();
  command::CommandMapEditor::translateAll();
  command::CommandMapEditorTranslation::translateAll();
  command::CommandMapTopLevelItem::translateAll();
  command::KeyCommandMapEditorTranslator::translateAll();
  command::MidiCommandMapEditorTranslator::translateAll();
  command::MidiName::translateAll();

  gui::audio::SetupPage::translateAll();

  music::MusicFileReader::translateAll();

  widget::tree::CD::translateAll();
  widget::tree::TreeViewDropAll::translateAll();
}

}  // namespace slow
}  // namespace rec
