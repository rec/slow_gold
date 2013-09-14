#include "rec/slow/CurrentFile.h"

#include "rec/audio/source/Player.h"
#include "rec/audio/util/BufferFiller.h"
#include "rec/audio/util/BufferedReader.h"
#include "rec/data/Data.h"
#include "rec/data/DataCenter.h"
#include "rec/data/DataOps.h"
#include "rec/data/UntypedDataListener.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/DropFiles.h"
#include "rec/gui/menu/RecentFiles.h"
#include "rec/gui/audio/Loops.h"
#include "rec/music/CreateMusicFileReader.h"
#include "rec/program/JuceModel.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/Instance.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/Threads.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Viewport.pb.h"
#include "rec/widget/waveform/Waveform.h"
#include "rec/widget/waveform/Zoom.h"

TRAN(RAN_OUT_OF_MEMORY, "Ran Out Of Memory For Your File");
TRAN(RAN_OUT_OF_MEMORY_FULL, "Sorry, there wasn't enough memory for the file.");

namespace rec {
namespace slow {

using namespace rec::data;
using namespace rec::widget::waveform;
using namespace juce;

void CurrentFile::operator()(const gui::DropFiles& dropFiles) {
  const file::VirtualFileList& files = dropFiles.files_;
  if (files.file_size() >= 1)
    setVirtualFile(files.file(0), true);
}

void CurrentFile::setFile(const File& f, bool showError) {
  setVirtualFile(file::toVirtualFile(f), showError);
}

void CurrentFile::operator()(const VirtualFile& vf) {
  setVirtualFile(vf, true);
}

const VirtualFile CurrentFile::file() const {
  return file_;
}

void CurrentFile::setVirtualFile(const VirtualFile& f, bool showError) {
  data::getDataCenter().waitTillClear();
  data::getDataCenter().clearUndoes();

  suspend();

  if (file_.path_size())
    gui::addRecentFile(file_, *getFileDescription());

  VirtualFile newFile = f;
  {
    Lock l(getInstance()->lock_);  // TODO: do we need this lock?
    file_.Swap(&newFile);
  }

  beforeFileChange();

  if (determineIfFileEmpty(showError))
    file_ = data::noData();
  else
    nonEmptyFileLoaded();

  afterFileChange(newFile);
  data::setProto(file_, CANT_UNDO);
  data::UntypedDataListener::setGlobalDataFile(file_);

  resume();
  program::menuItemsChanged();
}

unique_ptr<Message> CurrentFile::getFileDescription() {
  return unique_ptr<Message>(data::getData<music::Metadata>(file_)->clone());
}

const SampleTime CurrentFile::length() const {
  Lock l(lock_);
  return length_;
}

void CurrentFile::suspend() {
  getInstance()->player_->reset();
  getInstance()->reset();  // Stops the loading thread.
  getInstance()->currentTime_->reset();
}

void CurrentFile::resume() {
  if (file_.path_size())
    getInstance()->fillerThread_->startThread();
}

void CurrentFile::beforeFileChange() {
  MessageManagerLock l;
  auto& components = getInstance()->components_;
  components->waveform_->setLoading(true);
  components->waveform_->repaint();
}

void CurrentFile::afterFileChange(const VirtualFile& newFile) {
  MessageManagerLock l;
  auto& components = getInstance()->components_;

  if (not empty())
    components->directoryTree_->refreshNode(file_);

  if (newFile.path_size())
    components->directoryTree_->refreshNode(newFile);

  components->setEnabled(length_ != 0);
  components->waveform_->setLoading(false);
}

bool CurrentFile::determineIfFileEmpty(bool showError) {
  if (!file_.path_size()) {
    length_ = 0;
    return true;
  }

  music::MusicFileReader reader(file_);
  if (!reader.empty()) {
    getInstance()->bufferFiller_->setReader(file_, reader.release());
    length_ = getInstance()->bufferFiller_->length();
    if (length_)
      return false;
    reader.setError(t_RAN_OUT_OF_MEMORY, t_RAN_OUT_OF_MEMORY_FULL);
  }

  LookAndFeel::getDefaultLookAndFeel().setUsingNativeAlertWindows(true);

  if (showError) {
    juce::AlertWindow::showMessageBox(juce::AlertWindow::WarningIcon,
                                      reader.errorTitle(),
                                      reader.errorDetails());
  }

  file_.Clear();
  return true;
}

void CurrentFile::nonEmptyFileLoaded() {
  Viewport viewport = data::getProto<Viewport>(file_);

  if (!viewport.has_zoom()) {
    Zoom* zoom = viewport.mutable_zoom();
    *zoom = data::getProto<Zoom>(file_);  // Legacy files.
    if (!zoom->has_begin())
      zoom->set_begin(0);
    if (!zoom->has_end())
      zoom->set_end(length_);
  }

  if (!viewport.has_loop_points()) {
    LoopPointList* loops = viewport.mutable_loop_points();
    *loops = data::getProto<LoopPointList>(file_);  // Legacy files.
    if (!loops->loop_point_size())
      loops->add_loop_point()->set_selected(true);
  }

  viewport.mutable_loop_points()->set_length(length_);
  viewport.mutable_loop_points()->set_sample_rate(getInstance()->bufferFiller_->reader()->
                                                  reader()->sampleRate);
  data::setProto(viewport, file_, CANT_UNDO);
}

}  // namespace slow
}  // namespace rec
