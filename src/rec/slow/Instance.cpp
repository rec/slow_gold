#include "rec/slow/Instance.h"

#include "rec/app/GenericApplication.h"
#include "rec/audio/Device.h"
#include "rec/audio/source/FrameSource.h"
#include "rec/audio/source/Player.h"
#include "rec/gui/Dialog.h"
#include "rec/gui/audio/CommandBar.h"
#include "rec/gui/audio/TimeController.h"
#include "rec/gui/audio/TransformController.h"
#include "rec/gui/audio/TransportController.h"
#include "rec/slow/BufferFiller.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/GuiListener.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/Menus.h"
#include "rec/slow/MouseListener.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/Target.h"
#include "rec/slow/Threads.h"
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


Instance::Instance(SlowWindow* window) : window_(window) {
  menus_.reset(new Menus(this));
  device_.reset(new audio::Device);
  bufferFiller_.reset(new BufferFiller(this));
  currentFile_.reset(new CurrentFile(this));
  player_.reset(new audio::source::Player(device_.get()));
  components_.reset(new Components(this));
  currentTime_.reset(new CurrentTime(this));
  target_.reset(new Target(this));
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

  player_->timeBroadcaster()->addListener(components_->timeController_.get());
  player_->timeBroadcaster()->addListener(waveform->timeCursor());

  player_->level()->addListener(components_->transportController_->levelListener());

  ThumbnailBuffer* thumbnailBuffer = bufferFiller_->thumbnailBuffer();
  Source *s = new FrameSource<short, 2>(thumbnailBuffer->buffer()->frames());
  player_->setSource(s);
  player_->timeBroadcaster()->addListener(currentTime_.get());
  components_->waveform_->setAudioThumbnail(thumbnailBuffer->thumbnail());

  window->addListener(menus_.get());

  DialogLocker::getDisableBroadcaster()->addListener(target_->targetManager());
  DialogLocker::getDisableBroadcaster()->addListener(window->application());

  // TODO: move this elsewhere.
  Mode mode = data::getGlobal<Mode>();
  if (mode.click() == Mode::DRAW_LOOP_POINTS) {
    mode.clear_click();
    setProto(mode);
  }

  threads_->start();
}

Instance::~Instance() {
  player_->setState(audio::transport::STOPPED);
  threads_->stop();
}

void Instance::startup() {
  addUndoListener(menus_.get());
  menus_->menuItemsChanged();
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

void Instance::setProto(const Message& m, Undoable undoable) {
   return data::setProto(m, file(), undoable);
}

}  // namespace slow
}  // namespace rec
