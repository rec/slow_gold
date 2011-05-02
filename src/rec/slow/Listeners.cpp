#include "rec/slow/Listeners.h"
#include "rec/audio/source/BufferSource.h"
#include "rec/audio/source/CreateSourceAndLoadMetadata.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/data/persist/Persist.h"
#include "rec/data/Data.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/DropFiles.h"
#include "rec/gui/audio/LoopPoint.pb.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Target.h"
#include "rec/slow/Threads.h"
#include "rec/slow/ThreadData.h"
#include "rec/util/ClockUpdate.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/CursorTime.h"
#include "rec/widget/waveform/TimeAndMouseEvent.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace slow {

using namespace rec::audio::source;
using namespace rec::audio::stretch;
using namespace rec::audio::util;
using namespace rec::widget::tree;
using namespace rec::widget::waveform;
using namespace rec::gui::audio;

Listeners::Listeners(Instance* i) : HasInstance(i) {
  player()->addListener(this);

  Waveform* waveform = &components()->waveform_;
  waveform->dropBroadcaster()->addListener(this);
  waveform->addMouseListener(this, true);

  Root* root = &components()->directoryTree_;
  root->treeView()->dropBroadcaster()->addListener(this);
  root->addListener(persist::setter<VirtualFile>());

  persist::setter<VirtualFileList>()->addListener(root);
  (*root)(persist::get<VirtualFileList>());

  components()->transportController_.addListener(this);
}

void Listeners::operator()(const VirtualFile& f) {
  ptr<FileBuffer> buffer(new FileBuffer(f));
  ThreadData* threadData = threads()->data();
  if (!buffer->buffer_) {
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(f);
    return;
  }

  Switcher<FileBuffer>* switcher = &threadData->fileBuffer_;
  if (switcher->next()) {
    LOG(ERROR) << "Already reading file " << getFullDisplayName(f);
    return;
  }

  buffer->thumbnail_->addListener(&components()->waveform_);
  player()->setSource(new BufferSource(*buffer->buffer_->buffer()));
  switcher->setNext(buffer.transfer());
  threads()->data()->fetchThread_->notify();

  persist::Data<LoopPointList>* setter = persist::setter<LoopPointList>(f);
  components()->loops_.setData(setter);

  threadData->stretchLocker_.listenTo(persist::setter<Stretch>(f));
  threadData->loopLocker_.listenTo(setter);

  threadData->stretchLocker_.set(persist::get<Stretch>(f));
  threadData->loopLocker_.set(persist::get<LoopPointList>(f));

  components()->songData_.setFile(f);
}

static void toggle(Instance* i) { i->player_->toggle(); }

void Listeners::operator()(command::Command::Type t) {
  DLOG(INFO) << "Command " << command::Command::Type_Name(t);
  if (t == command::Command::ADD_LOOP_POINT) {

  } else if (t == command::Command::TOGGLE_START_STOP) {
    threads()->start(&toggle, "start/stop");
  }
}

void Listeners::operator()(RealTime) {}

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

void Listeners::operator()(const Stretch& x) {
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
    thread::callAsync(&components()->waveform_, &Waveform::addAllCursors, loops);
  }
}

void Listeners::mouseDoubleClick(const MouseEvent& e) {
  if (!target()->invokeDirectly(command::Command::OPEN))
    LOG(ERROR) << "Unable to start open dialog";
  else
    DLOG(INFO) << "Opened a new file!";
}

void Listeners::mouseDrag(const MouseEvent& e) {
  Waveform* waveform = &components()->waveform_;
  waveform->timeCursor()->setTime(waveform->xToTime(e.x));
}

void Listeners::mouseUp(const MouseEvent& e) {
  mouseDrag(e);

#ifdef TODO
  if (e.mods.isShiftDown())
    zoomOut();
  else if (zoomProto() && zoomProto()->get().click_to_zoom())
    zoomIn(timeMouse);

  else if (timeMouse.mouseEvent_->mods.isCommandDown())
    zoomIn(timeMouse);
#endif
}

void Listeners::operator()(const ClockTick&) {}
void Listeners::operator()(const ClockUpdate&) {}

void Listeners::operator()(const CursorTime&) {}
void Listeners::operator()(const TimeAndMouseEvent&) {}
void Listeners::operator()(const ZoomProto&) {}

void Listeners::operator()(audio::transport::State state) {
  thread::callAsync(&components()->transportController_,
                    &TransportController::setTransportState, state);
  player()->setState(state);
}

#ifdef TODO


#if 0
void Listeners::operator()(const file::VirtualFile& f) {
  persist::setter<VirtualFile>()->set(f);
  // ptr<PositionableAudioSource> source(empty(f) ? NULL : virtualFileSource(f));
  // components()->songData_.setFile(f);
  if (source)

  }

  if (empty(file)) {
    waveform_.setAudioThumbnail(NULL);
    instance_.clearData();

  } else {
    persist::Data<LoopPointList>* listData = persist::setter<LoopPointList>(file);
    loops_.setData(listData);
    waveform_.setData(listData);

    if (listData->get().loop_point_size())
      listData->requestUpdate();
    else
      listData->append(Address("loop_point"), Value(LoopPoint()));

    if (gui::CachedThumbnail* thumb = stretchyPlayer_.cachedThumbnail()) {
      waveform_.setAudioThumbnail(thumb->thumbnail());
      thumb->addListener(&waveform_);

    } else {
      LOG(ERROR) << "Can't get waveform for file " << file.ShortDebugString();
      return;
    }
    // gui::addRecentFile(file);

    // Adjust the length of clients - neaten this up!
    length_ = stretchyPlayer_.length() / 44100.0;
    (*(playbackController_.timeController()))(ClockUpdate(-1, length_));

    zoomProto()->requestUpdate();
  }

  (*this)(0.0);
#endif
}

void Listeners::operator()(SampleTime time) {
  components().timeController_.setTime(time);
  components().waveform_.timeCursor()->setTime(time);
  components().transportController_.setTime(time);
}

void Listeners::operator()(const juce::AudioThumbnail&) {
  components()->waveform_.repaint();
}

void Listeners::operator()(const TimeSelection& sel) {
  if (persist::Data<Stretch>* data = stretchyPlayer_.getStretchy()) {
    TimeRange range(sel);
    if (range.end_ < 0.0001)
      range.end_ = length_;

    audio::stretch::Loop loop;
    loop.set_begin(range.begin_);
    loop.set_end(range.end_);
    stretchyPlayer_.getTransport()->setOffset(range.begin_);

    DLOG(INFO) << "operator(): " << range.begin_ << ":" << range.end_;
    data->set("loop", loop);
  }
}

void Listeners::operator()(const widget::waveform::CursorTime& x) {
}

void Listeners::operator()(const widget::waveform::TimeAndMouseEvent& x) {

}

void Listeners::operator()(const widget::waveform::ZoomProto& x) {
}

void Listeners::operator()(RealTime x) {
}

void MainPage::clearTime() {
  if (stretchyPlayer_.getStretchy())
    stretchyPlayer_.getStretchy()->clear();
}

void MainPage::clearSelection() {
  loops_.clearSelection();
}

void MainPage::clearLoops() {
  loops_.clearLoops();
}

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
  // enableLoopPointButton(loops_.isNewLoopPoint(time));  // TODO
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

void MainPage::addLoopPoint() {
  loops_.addLoopPoint(stretchyPlayer_.getTransport()->getCurrentOffsetPosition());
  playbackController_.enableLoopPointButton(false);
}

#ifdef TODO
    double pos = transportSource_.getCurrentPosition();
    if (pos <= offset_ || pos >= offset_ + transportSource_.getLengthInSeconds())
      setPosition(offset_);
#endif

#endif

}  // namespace slow
}  // namespace rec

