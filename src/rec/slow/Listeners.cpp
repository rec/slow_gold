#include "rec/slow/Listeners.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/util/Gain.h"
#include "rec/data/Data.h"
#include "rec/data/persist/Persist.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/DropFiles.h"
#include "rec/util/LoopPoint.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Model.h"
#include "rec/slow/MouseListener.h"
#include "rec/slow/Target.h"
#include "rec/slow/Threads.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/thread/MakeCallback.h"
#include "rec/widget/waveform/Cursor.h"
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

  components()->transportController_.addListener(this);
  player()->timeBroadcaster()->addListener(&components()->timeController_);
  player()->timeBroadcaster()->addListener(waveform->timeCursor());

  player()->level()->addListener(components()->playerController_.levelListener());
}

Listeners::~Listeners() {}

void Listeners::operator()(SamplePosition time) {
  player()->setNextReadPosition(time);
}

void Listeners::operator()(command::Command::Type t) {
  if (!target()->targetManager()->invokeDirectly(t))
    LOG(ERROR) << "Failed to invoke " << command::Command::Type_Name(t);
}

void Listeners::operator()(const Stretch& x) {
  player()->setStretch(x);
}

void Listeners::operator()(const StereoProto& x) {
  player()->setStereoProto(x);
}

void Listeners::operator()(None) {
  thread::callAsync(&components()->waveform_, &Waveform::repaint);
}

void Listeners::operator()(const audio::Gain& g) {
  float gain = audio::getGain(g);
  player()->setGain(gain);
  components()->playerController_.levelMeter()->setGain(gain);
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
  if (list.file_size() < 1)
    LOG(ERROR) << "file size=" << list.file_size();
  else
    persist::set(list.file(0));
}

void Listeners::operator()(audio::transport::State state) {
  thread::callAsync(&components()->transportController_,
                    &TransportController::setTransportState, state);
  player()->setState(state);
  player()->level()->clear();
}

#ifdef TODO

void MainPage::loadRecentFile(int menuItemId) {
  gui::RecentFiles recent = gui::getSortedRecentFiles();
  const VirtualFile& file = recent.file(menuItemId).file();
  persist::setter<VirtualFile>()->set(file);
}

static const int BLOCKSIZE = 1024;
static const int SAMPLE_RATE = 44100;

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

#endif

}  // namespace slow
}  // namespace rec

