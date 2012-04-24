#include "rec/slow/CurrentFile.h"

#include "rec/audio/source/Player.h"
#include "rec/audio/util/BufferFiller.h"
#include "rec/command/Command.h"
#include "rec/data/Data.h"
#include "rec/data/DataCenter.h"
#include "rec/data/DataOps.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/audio/Loops.h"
#include "rec/gui/DropFiles.h"
#include "rec/gui/RecentFiles.h"
#include "rec/gui/audio/TransformController.h"
#include "rec/gui/audio/TimeController.h"
#include "rec/music/CreateMusicFileReader.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/Menus.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/Target.h"
#include "rec/slow/Threads.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Waveform.h"
#include "rec/widget/waveform/Viewport.pb.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace slow {

namespace {

const int FILLER_THREAD_STOP_TIME = 1000;

Trans RAN_OUT_OF_MEMORY("Ran Out Of Memory For Your File");
Trans RAN_OUT_OF_MEMORY_FULL("Your file was so large that the program "
                             "ran out of memory.");
}

using namespace rec::widget::waveform;

CurrentFile::CurrentFile(Instance* i) : HasInstance(i),
                                        initialized_(false),
                                        hasStarted_(false) {
}

CurrentFile::~CurrentFile() {}

void CurrentFile::operator()(const gui::DropFiles& dropFiles) {
  const file::VirtualFileList& files = dropFiles.files_;
  if (files.file_size() >= 1)
    setFile(files.file(0));
}

void CurrentFile::setFile(const VirtualFile& f) {
  while (data::getDataCenter().hasUpdates())
    Thread::sleep(1);

  Lock l(instance_->lock_);
  if (!initialized_)
    initialized_ = true;
  else if (data::equals(f, file_))
    return;

  player()->reset();
  instance_->fillerThread_->stopThread(FILLER_THREAD_STOP_TIME);

  if (!empty())
    gui::addRecentFile(file_, data::get<music::Metadata>(&file_));

  VirtualFile oldFile = file_;
  file_ = f;

  length_ = getFileLength();
  setViewport();

  currentTime()->setTime(0);
  currentTime()->jumpToTime(0);
  currentTime()->setViewport(viewport_);
  components()->waveform_->setViewport(viewport_);

  components()->setEnabled(!empty());
  components()->directoryTree_->refreshNode(oldFile);
  components()->directoryTree_->refreshNode(file_);

  menus()->menuItemsChanged();
  instance_->fillerThread_->startThread();

  data::setGlobal(file_);
}

int64 CurrentFile::getFileLength() {
  if (file::empty(file_))
    return 0;

  music::MusicFileReader reader(file_);
  if (!reader.empty()) {
    if (int64 len = bufferFiller()->setReader(file_, reader.transfer()))
      return len;
    reader.setError(RAN_OUT_OF_MEMORY, RAN_OUT_OF_MEMORY_FULL);
  }

  if (hasStarted_) {
    juce::AlertWindow::showMessageBox(juce::AlertWindow::WarningIcon,
                                      reader.errorTitle(),
                                      reader.errorDetails());
  }

  file_.Clear();
  return 0;
}

void CurrentFile::setViewport() {
  if (!length_) {
    viewport_.Clear();
    return;
  }
  viewport_ = data::getProto<Viewport>(&file_);
  bool mustUpdate = false;
  if (!viewport_.has_zoom()) {
    mustUpdate = true;

    Zoom* zoom = viewport_.mutable_zoom();
    *zoom = data::getProto<Zoom>(&file_);
    if (!zoom->has_begin())
      zoom->set_begin(0);
    if (!zoom->has_end())
      zoom->set_end(length_);
  }

  if (!viewport_.has_loop_points()) {
    mustUpdate = true;
    LoopPointList* loops = viewport_.mutable_loop_points();
    *loops = data::getProto<LoopPointList>(&file_);
    if (loops->length() != length_)
      loops->set_length(length_);
    if (!loops->loop_point_size())
      loops->add_loop_point()->set_selected(true);
  }

  if (length_ != viewport_.loop_points().length()) {
    mustUpdate = true;
    viewport_.mutable_loop_points()->set_length(length_);
  }

  if (!viewport_.loop_points().loop_point_size()) {
    mustUpdate = true;
    viewport_.mutable_loop_points()->add_loop_point()->set_selected(true);
  }

  if (mustUpdate)
    data::setProto(viewport_, file_);
}

void CurrentFile::translateAll() {
  RAN_OUT_OF_MEMORY.translate();
  RAN_OUT_OF_MEMORY_FULL.translate();
}

}  // namespace slow
}  // namespace rec

