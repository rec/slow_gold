#include "rec/slow/Listeners.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/data/Data.h"
#include "rec/data/persist/Persist.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/DropFiles.h"
#include "rec/gui/audio/LoopPoint.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Model.h"
#include "rec/slow/MouseListener.h"
#include "rec/slow/Target.h"
#include "rec/slow/Threads.h"
#include "rec/util/ClockUpdate.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/thread/MakeCallback.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/CursorTime.h"
#include "rec/widget/waveform/TimeAndMouseEvent.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace slow {

using namespace rec::audio::source;
using namespace rec::audio::stretch;
using namespace rec::audio::util;
using namespace rec::gui::audio;
using namespace rec::widget::tree;
using namespace rec::widget::waveform;

Listeners::Listeners(Instance* i)
  	: HasInstance(i), mouseListener_(new slow::MouseListener(i)) {
  player()->addListener(this);

  WaveformComp* waveform = &components()->waveform_;
  waveform->dropBroadcaster()->addListener(this);

  Root* root = &components()->directoryTree_;
  root->treeView()->dropBroadcaster()->addListener(this);
  root->addListener(persist::setter<VirtualFile>());

  persist::setter<VirtualFileList>()->addListener(root);
  (*root)(persist::get<VirtualFileList>());

  components()->transportController_.addListener(this);
  player()->timeBroadcaster()->addListener(&components()->timeController_);
  player()->timeBroadcaster()->addListener(waveform->timeCursor());
}

void Listeners::operator()(SampleTime time) {
  // Waveform* waveform = &components()->waveform_;
  // waveform->timeCursor()->setListeningToClock(true); TODO
  player()->setNextReadPosition(time);
}

void Listeners::operator()(command::Command::Type t) {
  if (!target()->invokeDirectly(t))
    LOG(ERROR) << "Failed to invoke " << command::Command::Type_Name(t);
}

void Listeners::operator()(const Stretch& x) {
}

void Listeners::operator()(None) {
  thread::callAsync(&components()->waveform_, &Waveform::repaint);
}

void Listeners::operator()(const gui::DropFiles& dropFiles) {
  const file::VirtualFileList& files = dropFiles.files_;
  if (dropFiles.target_ == &components()->waveform_) {
    if (files.file_size() >= 1)
      persist::set(files.file(0));

    LOG_IF(ERROR, files.file_size() != 1);

  } else if (dropFiles.target_ == components()->directoryTree_.treeView()) {
    using file::getFile;

    typedef std::set<string> FileSet;
    FileSet existing;
    VirtualFileList list(persist::get<file::VirtualFileList>());
    for (int i = 0; i < list.file_size(); ++i)
      existing.insert(str(getFile(list.file(i)).getFullPathName()));

    for (int i = 0; i < files.file_size(); ++i) {
      if (existing.find(str(getFile(files.file(i)).getFullPathName())) == existing.end())
        data::append(persist::setter<file::VirtualFileList>(), Address("file"), files.file(i));
    }
  }
}

void Listeners::operator()(const VirtualFileList& list) {
  if (list.file_size() != 1)
    LOG(ERROR) << "file size=" << list.file_size();
  else
    model()->fileLocker()->set(list.file(0));
}

void Listeners::operator()(const LoopPointList& loops) {
  if (!loops.loop_point_size()) {
    LoopPointList loop;
    loop.add_loop_point();
    loop.add_selected(true);
    persist::set(loop, persist::get<VirtualFile>());
  } else {
    components()->loops_.setData(persist::setter<LoopPointList>(
        persist::get<VirtualFile>()));  // TODO
    thread::callAsync(&components()->waveform_, &Waveform::addAllCursors,
                      loops);
    model()->setLoopPointList(loops);
  }
}

void Listeners::operator()(audio::transport::State state) {
  thread::callAsync(&components()->transportController_,
                    &TransportController::setTransportState, state);
  player()->setState(state);
}

#ifdef TODO

void MainPage::zoomIn(const TimeAndMouseEvent& timeMouse) {
  if (persist::Data<ZoomProto>* z = zoomProto())
    z->set(Address(), waveform::zoomIn(*z, length_, timeMouse.time_));
}

void MainPage::zoomOut() {
  if (persist::Data<ZoomProto>* z = zoomProto())
    z->set(Address(), waveform::zoomOut(*z, length_));
}

void MainPage::loadRecentFile(int menuItemId) {
  gui::RecentFiles recent = gui::getSortedRecentFiles();
  const VirtualFile& file = recent.file(menuItemId).file();
  persist::setter<VirtualFile>()->set(file);
}

void MainPage::cut() {
#if 0
  string s = yaml::write(prefs);
  SystemClipboard::copyTextToClipboard(s.c_str());
  DLOG(INFO) << s;
#endif
}

void MainPage::paste() {
#if 0
  string s = SystemClipboard::getTextFromClipboard();
  DLOG(INFO) << s;
  yaml::read(s, &prefs);
#endif
}

static const int BLOCKSIZE = 1024;
static const int SAMPLE_RATE = 44100;

void Waveform::operator()(const ZoomProto& zp) {
  ScopedLock l(lock_);
  zoom_ = zp;
  if (!zoom_.has_end())
    zoom_.set_end(thumbnail_ ? thumbnail_->getTotalLength() : 0);

  resized();
}

void Waveform::operator()(const gui::LoopPointList& loopPoints) {
}

  class ZoomData : public DataListener<ZoomProto> {
   public:
    ZoomData(Waveform* waveform) : waveform_(waveform) {}
    virtual void operator()(const ZoomProto& zoom) { (*waveform_)(zoom); }

   private:
    Waveform* const waveform_;

    DISALLOW_COPY_ASSIGN_AND_EMPTY(ZoomData);
  };

  ZoomData zoomData_;

void PlaybackController::operator()(const Stretch& desc) {
  thread::callAsync(&stretchyController_,
                    &gui::StretchyController::enableSliders,
                    !desc.stretch().disabled());
  timeController_(desc);
}

void PlaybackController::operator()(RealTime time) {
  enableLoopPointButton(loops_.isNewLoopPoint(time));  // TODO
}

void PlaybackController::enableLoopPointButton(bool e) {
  if (e != transportController_.getLoopPointButtonEnabled()) {
    thread::callAsync(&transportController_,
                      &gui::TransportController::enableLoopPointButton,
                      e);
  }
}

void Loops::operator()(const widget::waveform::CursorTime& ct) {
  if (ct.cursor_ >= 0)
    getData()->set(Address("loop_point", ct.cursor_, "time"), ct.time_);
  else
    timeBroadcaster_.broadcast(ct.time_);
}

void StretchyPlayer::operator()(const VirtualFile& file) {
  {
    ScopedLock l(lock_);
    if (file_ == file)
      return;
  }

  persist::Data<Stretch>* stretchy = NULL;
  thread_ptr<audio::source::DoubleRunnyBuffer> dr;
  if (!empty(file)) {
    stretchy = persist::setter<Stretch>(file);
    dr.reset(new audio::source::DoubleRunnyBuffer(file, stretchy));
  }

  {
    ScopedLock l(lock_);
    file_ = file;
    timeLocker_->initialize(0);
    transportSource_->clear();
    dr.swap(doubleRunny_);
    transportSource_->audioTransportSource()->setSource(doubleRunny_->doubleStretchy());
    stretchy_ = stretchy;
    if (stretchy_)
      stretchy_->requestUpdate();
  }

  broadcast(file);
}

void StretchyPlayer::operator()(const double& t) {
  // This is only called when the user clicks in the window to set a new
  // playback position.
  if (stretchy_ && (!doubleRunny_ || doubleRunny_->fillFromPosition(44100 * t)))
    transportSource_->setPosition(stretchy_->get().stretch().time_scale() * t);

  else
    LOG(ERROR) << "Failed to fill buffer.";
}

gui::CachedThumbnail* StretchyPlayer::cachedThumbnail() {
  return doubleRunny_? doubleRunny_->cachedThumbnail() : NULL;
}

int StretchyPlayer::length() const {
  return doubleRunny_ ? doubleRunny_->getTotalLength() : 0;
}

#ifdef TODO
    double pos = transportSource_.getCurrentPosition();
    if (pos <= offset_ || pos >= offset_ + transportSource_.getLengthInSeconds())
      setPosition(offset_);
#endif

#endif

}  // namespace slow
}  // namespace rec

