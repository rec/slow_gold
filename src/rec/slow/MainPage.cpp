#include <google/protobuf/descriptor.h>

#include "rec/slow/MainPage.h"
#include "rec/gui/RecentFiles.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/Zoom.h"

using namespace juce;

using namespace rec::audio::source;
using namespace rec::widget::waveform;

namespace rec {
namespace slow {

MainPage::MainPage(Instance* instance) //
    : Layout("MainPage"),
      instance_(instance),
      stretchyPlayer_(instance_),
      directoryTreeRoot_(new Root(widget::tree::NodeDesc())),
      waveform_(instance_, WaveformProto()),
      playbackController_(instance_, stretchyPlayer_.getTransport()),
      openDialogOpen_(false),
      audioSetupPage_(instance_->device_) {
  doLayout();

  Broadcasters* broadcasters = instance_->broadcasters();

  broadcasters->realTime_->addListener(this);
  broadcasters->timeAndMouseEvent_.addListener(this);
  broadcasters->selectionRange_->addListener(this);
  broadcasters->virtualFile->addListener(this);

  broadcasters->realTime_->addListener(waveform_.timeCursor());
  broadcasters->realTime_->addListener(playbackController_.timeController());
  broadcasters->selectionRange_->addListener(playbackController_.timeController());
  broadcasters->cursorTime_->addListener(&loops_);
  broadcasters->virtualFile->addListener(stretchyPlayer_.fileListener());
  broadcasters_->realTimeBroadcaster_->addListener(&stretchyPlayer_);

  directoryTreeRoot_->startThread();
  if (persist::Data<VirtualFile>* d = instance_.data().virtualFile_)
    d->requestUpdate();

  (*this)(0.0);
}

void MainPage::operator()(double time) {
  playbackController_.enableLoopPointButton(loops_.isNewLoopPoint(time));
}

void MainPage::addResizer(ptr<SetterResizer>* r, const char* addr, Layout* lo) {
  r->reset(new SetterResizer(Address(addr), lo, lo->size()));
  (*r)->add();
}

MainPage::~MainPage() {
  // stretchyPlayer_.getTransport()->clear();
}

void MainPage::paint(Graphics& g) {
  g.fillAll(Colours::lightgrey);
}

static const int BLOCKSIZE = 1024;
static const int SAMPLE_RATE = 44100;

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

  else if (timeMouse.clickCount_ > 1)
    thread::callAsync(this, &MainPage::doOpen);

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

}  // namespace slow
}  // namespace rec
