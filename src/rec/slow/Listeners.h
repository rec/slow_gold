#ifndef __REC_SLOW_LISTENERS__
#define __REC_SLOW_LISTENERS__

#include "rec/util/Listener.h"

namespace rec {
namespace slow {

class Listeners :
    public Listener<const ClockUpdate&>,
    public Listener<const SelectionRange&>,
    public Listener<const audio::stretch::StretchLoop&>,
    public Listener<const file::VirtualFile&>,
    public Listener<const file::VirtualFileList&>,
    public Listener<const gui::LoopPointList&>,
    public Listener<const widget::waveform::CursorTime&>,
    public Listener<const widget::waveform::TimeAndMouseEvent&>,
    public Listener<const widget::waveform::ZoomProto&>,
    public Listener<RealTime>,
    public Listener<TransportState> {
 public:
  virtual void operator()(const ClockUpdate&) {}
  virtual void operator()(const SelectionRange&) {}
  virtual void operator()(const audio::stretch::StretchLoop&) {}
  virtual void operator()(const file::VirtualFile&) {}
  virtual void operator()(const file::VirtualFileList&) {}
  virtual void operator()(const gui::LoopPointList&) {}
  virtual void operator()(const widget::waveform::CursorTime&) {}
  virtual void operator()(const widget::waveform::TimeAndMouseEvent&) {}
  virtual void operator()(const widget::waveform::ZoomProto&) {}
  virtual void operator()(RealTime) {}
  virtual void operator()(TransportState) {}
};

void MainPage::addLoopPoint() {
  loops_.addLoopPoint(stretchyPlayer_.getTransport()->getCurrentOffsetPosition());
  playbackController_.enableLoopPointButton(false);
}

void MainPage::operator()(const TimeAndMouseEvent& timeMouse) {
  if (timeMouse.mouseEvent_->mods.isShiftDown())
    zoomOut();

  else if (zoomProto() && zoomProto()->get().click_to_zoom())
    zoomIn(timeMouse);

  else if (timeMouse.mouseEvent_->mods.isCommandDown())
    zoomIn(timeMouse);

#ifdef TODO
  else if (timeMouse.clickCount_ > 1)
    thread::callAsync(this, &MainPage::doOpen);
#endif

  else
    stretchyPlayer_.setTime(timeMouse.time_);
}

void MainPage::operator()(const VirtualFile& file) {
  playbackController_(file);

  if (empty(file)) {
    waveform_.setAudioThumbnail(NULL);
    instance_.clearData();
    length_ = 0;

  } else {
    persist::Data<LoopPointList>* listData = persist::data<LoopPointList>(file);
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
    gui::addRecentFile(file);

    // Adjust the length of clients - neaten this up!
    length_ = stretchyPlayer_.length() / 44100.0;
    (*(playbackController_.timeController()))(ClockUpdate(-1, length_));

    zoomProto()->requestUpdate();
  }

  (*this)(0.0);
}

void MainPage::operator()(const SelectionRange& sel) {
  if (persist::Data<StretchLoop>* data = stretchyPlayer_.getStretchy()) {
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
  persist::data<VirtualFile>()->set(file);
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
  string s = SystemClipboard::getTextFromClipboard().toCString();
  DLOG(INFO) << s;
  yaml::read(s, &prefs);
#endif
}

static const int BLOCKSIZE = 1024;
static const int SAMPLE_RATE = 44100;

void Waveform::operator()(const juce::AudioThumbnail&) {
  thread::runOnMessageThread(this, &Waveform::repaint);
}

void Waveform::operator()(const ZoomProto& zp) {
  ScopedLock l(lock_);
  zoom_ = zp;
  if (!zoom_.has_end())
    zoom_.set_end(thumbnail_ ? thumbnail_->getTotalLength() : 0);

  resized();
}

void Waveform::operator()(const gui::LoopPointList& loopPoints) {
  thread::callAsync(this, &Waveform::addAllCursors, loopPoints);
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

void PlaybackController::operator()(const StretchLoop& desc) {
  thread::callAsync(&stretchyController_,
                    &gui::StretchyController::enableSliders,
                    !desc.stretch().disabled());
  timeController_(desc);
}

void PlaybackController::operator()(const VirtualFile& file) {
  songData_.setData(empty(file) ? NULL : persist::data<cd::Metadata>(file));
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

  persist::Data<StretchLoop>* stretchy = NULL;
  thread_ptr<audio::source::DoubleRunnyBuffer> dr;
  if (!empty(file)) {
    stretchy = persist::data<StretchLoop>(file);
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

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_LISTENERS__
