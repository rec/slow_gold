#include "rec/slow/Instance.h"

#include "rec/app/AppSettings.pb.h"
#include "rec/app/GenericApplication.h"
#include "rec/app/RegisterInstance.h"
#include "rec/audio/Device.h"
#include "rec/audio/OutputSampleRate.h"
#include "rec/audio/source/FrameSource.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/util/BufferFiller.h"
#include "rec/audio/util/BufferedReader.h"
#include "rec/base/SampleRate.h"
#include "rec/data/DataCenter.h"
#include "rec/data/DataOps.h"
#include "rec/data/UndoStack.h"
#include "rec/gui/Dialog.h"
#include "rec/gui/LookAndFeel.h"
#include "rec/gui/audio/CommandBar.h"
#include "rec/gui/audio/TimeController.h"
#include "rec/gui/audio/TransformController.h"
#include "rec/gui/audio/TransportController.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/FillerThread.h"
#include "rec/slow/GuiListener.h"
#include "rec/slow/GuiSettings.h"
#include "rec/slow/IsWholeSong.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/Menus.h"
#include "rec/slow/MouseListener.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/Target.h"
#include "rec/slow/Threads.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/Undo.h"
#include "rec/util/file/FileType.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/thread/Trash.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Cursor.h"

namespace rec {
namespace slow {

using namespace rec::app;
using namespace rec::audio::source;
using namespace rec::audio::util;
using namespace rec::audio;
using namespace rec::widget::waveform;

using gui::DialogLocker;

static const int MS_TILL_TOOLTIP = 700;
static const int FILLER_PRIORITY = 4;

using juce::TooltipWindow;

namespace {

class IsWholeSongInstance : public IsWholeSong, public HasInstance {
 public:
  IsWholeSongInstance(Instance* i) : HasInstance(i) {}

  virtual IsWholeSong::WholeSong isWholeSong() const {
    if (empty())
      return SONG_IS_ONE_SEGMENT;

    LoopPointList lpl = data::getProto<Viewport>(file()).loop_points();
    return (lpl.loop_point_size() <= 1) ? IsWholeSong::SONG_IS_ONE_SEGMENT :
      (audio::getSelectionCount(lpl) == 1) ? IsWholeSong::ONE_SEGMENT :
      IsWholeSong::WHOLE_SONG;
  }
};

static Instance* INSTANCE = NULL;

}  // namespace

Instance::Instance(app::Window* window) : window_(window) {
  CHECK_DDD(51, 2193, int64, int32);
  DCHECK(!INSTANCE);
  INSTANCE = this;
}

// static
Instance* Instance::getInstance() { return INSTANCE; };

// static
const VirtualFile Instance::getInstanceFile() { return INSTANCE->file(); };

void Instance::init() {
  window_->init();
  menus_.reset(new Menus(this, new IsWholeSongInstance(this)));
  device_.reset(new audio::Device);
  currentFile_.reset(new CurrentFile(this));

  doLog("Player\n");
  player_.reset(new audio::source::Player(device_.get()));

  doLog("Player initialize\n");
  player_->init();

  doLog("Components\n");
  components_.reset(new Components(this));

  doLog("Target\n");
  target_.reset(new Target(this));

  doLog("CurrentTime\n");
  currentTime_.reset(new CurrentTime(this));

  doLog("BufferFiller\n");
  bufferFiller_.reset(new BufferFiller);

  doLog("LookAndFeel\n");
  lookAndFeel_.reset(new gui::LookAndFeel);

  doLog("MouseListener\n");
  mouseListener_.reset(new MouseListener(this));
  guiListener_.reset(new GuiListener(this));
  fillerThread_.reset(new FillerThread(this));
  threads_.reset(new Threads(this));

  doLog("Components::init\n");
  components_->init();

  fillerThread_->setPriority(FILLER_PRIORITY);

  target_->addCommands();
  player_->addListener(components_->transportController_.get());
  audio::getOutputSampleRateBroadcaster()->addListener(player_.get());

	typedef gui::DropTarget<Waveform> DropWave;
  DropWave* waveform = dynamic_cast<DropWave*>(components_->waveform_.get());
  waveform->dropBroadcaster()->addListener(currentFile_.get());

  widget::tree::Root* root = components_->directoryTree_.get();
  root->treeView()->dropBroadcaster()->addListener(currentFile_.get());
  root->addListener(currentFile_.get());
  // components_->mainPage_->dropBroadcaster()->addListener(currentFile_.get());

  components_->transportController_->addListener(target_->targetManager());
  components_->commandBar_->addListener(target_->targetManager());

  player_->timer()->addListener(components_->timeController_.get());
  player_->timer()->addListener(waveform->timeCursor());
  player_->timer()->addListener(currentTime_.get());

  player_->level()->addListener(components_->transportController_->levelListener());

  player_->setSource(makeSource());
  components_->waveform_->setAudioThumbnail(bufferFiller_->thumbnail());

  window_->addListener(menus_.get());

  DialogLocker::getDisableBroadcaster()->addListener(target_->targetManager());
  DialogLocker::getDisableBroadcaster()->addListener(window_->application());

#ifdef DRAW_LOOP_POINTS_IS_ONE_CLICK
  // TODO: move this elsewhere.
  Mode mode = data::getProto<Mode>();
  if (mode.click() == Mode::DRAW_LOOP_POINTS) {
    mode.clear_click();
    setProto(mode);
  }
#endif
  doLog("end Instance::init\n");
}

audio::Source* Instance::makeSource() const {
  return bufferFiller_->reader()->makeSource();
}

Instance::~Instance() {
  player_->setState(audio::transport::STOPPED);
  device_->shutdown();
  threads_.reset();
}

void Instance::startup() {
  LOG(INFO) << "Instance::startip";

  addUndoListener(menus_.get());
  menus_->menuItemsChanged();

  LOG(INFO) << "Finished creating the menus";

  VirtualFile vf = data::getProto<VirtualFile>();
  if (vf.type() != VirtualFile::NONE) {
    File f = file::toRealFile(vf);
    vf = file::toVirtualFile(f);
    data::setProto(vf);
  }

  LOG(INFO) << "Finished setting the file as data";

  {
    MessageManagerLock l;
    juce::LookAndFeel::setDefaultLookAndFeel(lookAndFeel_.get());

    window_->toFront(true);
    currentFile_->setVirtualFile(vf, false);
  }

  LOG(INFO) << "Finished look and feel/settings file";

  thread::callAsync(window_, &DocumentWindow::setVisible, true);
  threads_->start();
  Thread* timer = threads_->timerThread();
  components_->transportController_->timeController()->setThread(timer);
  player_->timer()->setThread(timer);

  LOG(INFO) << "Finished Instance::startup!";
}

class RegisterSlow : public app::RegisterInstance {
 public:
  RegisterSlow() {}

  virtual void onSuccess() {
    data::Opener<AppSettings> settings(data::global(), CANT_UNDO);
    settings->set_registered(true);
  }
};

void Instance::postStartup() {
  LOG(INFO) << "Instance::postStartup!";

  data::getDataCenter().undoStack()->setEnabled();
  LOG(INFO) << "got data center!";

  if (!data::getProto<AppSettings>().registered())
    thread::trash::run<RegisterSlow>();

  LOG(INFO) << "registered";

  MessageManagerLock l;
  if (data::getProto<GuiSettings>().show_about_on_startup())
    window_->startAboutWindow();

  LOG(INFO) << "Instance::postStartup finished";

}

const VirtualFile Instance::file() const {
  return currentFile_->file();
}

void Instance::updateGui() {
  guiListener_->update();
}

SampleTime Instance::length() const {
  return currentFile_->length();
}

SampleTime Instance::time() const {
  return currentTime_->time();
}

bool Instance::isPlaying() const {
  return player_ && player_->state();
}

bool Instance::empty() const {
  return currentFile_ && currentFile_->empty();
}

void Instance::setProto(const Message& m, Undoable undoable) {
   data::setProto(m, file(), undoable);
   menus_->menuItemsChanged();
}

void Instance::reset() {
  fillerThread_->stopThread(FILLER_THREAD_STOP_TIME);
  bufferFiller_->reset();
}

SampleRate Instance::getSourceSampleRate() const {
  return data::getProto<Viewport>(file()).loop_points().sample_rate();
}

}  // namespace slow
}  // namespace rec
