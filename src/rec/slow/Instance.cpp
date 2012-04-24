#include "rec/slow/Instance.h"

#include "rec/app/GenericApplication.h"
#include "rec/audio/Device.h"
#include "rec/audio/source/FrameSource.h"
#include "rec/audio/source/Player.h"
#include "rec/gui/Dialog.h"
#include "rec/data/DataOps.h"
#include "rec/gui/LookAndFeel.h"
#include "rec/gui/audio/CommandBar.h"
#include "rec/gui/audio/TimeController.h"
#include "rec/gui/audio/TransformController.h"
#include "rec/gui/audio/TransportController.h"
#include "rec/slow/BufferFiller.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/GuiListener.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/IsWholeSong.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/Menus.h"
#include "rec/slow/MouseListener.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/Target.h"
#include "rec/slow/Threads.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/Undo.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Cursor.h"

namespace rec {
namespace slow {

using namespace rec::audio;
using namespace rec::audio::util;
using namespace rec::audio::source;
using namespace rec::widget::waveform;

using gui::DialogLocker;

static const int MS_TILL_TOOLTIP = 700;

using juce::TooltipWindow;

namespace {

class IsWholeSongInstance : public IsWholeSong, public HasInstance {
 public:
  IsWholeSongInstance(Instance* i) : HasInstance(i) {}

  virtual IsWholeSong::WholeSong isWholeSong() const {
    LoopPointList lpl = data::getProto<LoopPointList>(file());
    return (lpl.loop_point_size() <= 1) ? IsWholeSong::SONG_IS_ONE_SEGMENT :
      (audio::getSelectionCount(lpl) == 1) ? IsWholeSong::ONE_SEGMENT :
      IsWholeSong::WHOLE_SONG;
  }
};

}  // namespace

Instance::Instance(SlowWindow* window) : window_(window) {
  CHECK_DDD(51, 2193, int64, int32);

  menus_.reset(new Menus(this, new IsWholeSongInstance(this)));
  device_.reset(new audio::Device);
  currentFile_.reset(new CurrentFile(this));
  player_.reset(new audio::source::Player(device_.get()));
  components_.reset(new Components(this));
  target_.reset(new Target(this));
  currentTime_.reset(new CurrentTime(this));
  bufferFiller_.reset(new BufferFiller);
  lookAndFeel_.reset(new gui::LookAndFeel);

#ifdef SET_FILE_EARLY
  currentFile_->setFile(data::getGlobal<VirtualFile>());
#endif

  mouseListener_.reset(new MouseListener(this));
  guiListener_.reset(new GuiListener(this));
  threads_.reset(new Threads(this));

  target_->addCommands();
  player_->addListener(components_->transportController_.get());
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
  DialogLocker::getDisableBroadcaster()->addListener(window->application());

#ifdef DRAW_LOOP_POINTS_IS_ONE_CLICK
  // TODO: move this elsewhere.
  Mode mode = data::getGlobal<Mode>();
  if (mode.click() == Mode::DRAW_LOOP_POINTS) {
    mode.clear_click();
    setProto(mode);
  }
#endif

  threads_->start();
}

audio::Source* Instance::makeSource() const {
  return bufferFiller_->reader()->makeSource();
}

Instance::~Instance() {
  player_->setState(audio::transport::STOPPED);
  device_->shutdown();
  threads_.reset();
}

void Instance::init() {
  menus_->init();
  player_->init();
  components_->init();
  currentFile_->init();
  currentTime_->init();
  guiListener_->init();
  mouseListener_->init();
}

void Instance::startup() {
  addUndoListener(menus_.get());
  menus_->menuItemsChanged();

  MessageManagerLock l;
  window_->toFront(true);
  juce::LookAndFeel::setDefaultLookAndFeel(lookAndFeel_.get());
  currentFile_->hasStarted();
  if (data::getGlobal<GuiSettings>().show_about_on_startup())
    window_->startAboutWindow();
}

const VirtualFile Instance::file() const {
  return currentFile_->virtualFile();
}

void Instance::updateGui() {
  guiListener_->update();
}

Samples<44100> Instance::length() const {
  return currentFile_->length();
}

Samples<44100> Instance::time() const {
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

}  // namespace slow
}  // namespace rec
