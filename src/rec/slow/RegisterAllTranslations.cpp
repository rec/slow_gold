#include "rec/slow/RegisterAllTranslations.h"
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
#include "rec/slow/CurrentFile.h"
#include "rec/slow/callbacks/InstanceCallbacks.h"
#include "rec/slow/callbacks/GlobalCallbacks.h"
#include "rec/slow/callbacks/SaveFile.h"
#include "rec/support/RequestSupport.h"
#include "rec/util/cd/CDReader.h"
#include "rec/widget/tree/CD.h"
#include "rec/widget/tree/TreeViewDropAll.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace slow {

void registerAllTranslations() {
  AboutWindow::registerAllTranslations();
  CurrentFile::registerAllTranslations();
  GlobalCallbacks::registerAllTranslations();
  InstanceCallbacks::registerAllTranslations();
  SaveFile::registerAllTranslations();

  app::DownloadVersion::registerAllTranslations();

  command::CommandEntryWindow::registerAllTranslations();
  command::CommandMapEditButton::registerAllTranslations();
  command::CommandMapEditor::registerAllTranslations();
  command::CommandMapEditorTranslation::registerAllTranslations();
  command::CommandMapTopLevelItem::registerAllTranslations();
  command::KeyCommandMapEditorTranslator::registerAllTranslations();
  command::MidiCommandMapEditorTranslator::registerAllTranslations();
  command::MidiName::registerAllTranslations();

  gui::audio::SetupPage::registerAllTranslations();

  music::MusicFileReader::registerAllTranslations();

  support::RequestSupport::registerAllTranslations();
  util::cd::CDReader::registerAllTranslations();
  widget::tree::CD::registerAllTranslations();
  widget::tree::TreeViewDropAll::registerAllTranslations();
  widget::waveform::Waveform::registerAllTranslations();
}

}  // namespace slow
}  // namespace rec

