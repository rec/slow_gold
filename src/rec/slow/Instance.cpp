#include "rec/slow/Instance.h"

#include "rec/app/GenericApplication.h"
#include "rec/audio/Device.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/source/FrameSource.h"
#include "rec/gui/Dialog.h"
#include "rec/gui/audio/PlayerController.h"
#include "rec/gui/audio/TimeController.h"
#include "rec/gui/audio/TransportController.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/Menus.h"
#include "rec/slow/BufferFiller.h"
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

Instance::Instance(SlowWindow* window)
    : window_(window),
      menus_(new Menus(this)),
      components_(new Components(this)),
      device_(new audio::Device),
      player_(new audio::source::Player(device_.get())),
      currentFile_(new CurrentFile(this)),
      currentTime_(new CurrentTime(this)),
      bufferFiller_(new BufferFiller(this)),
      target_(new Target(this)),
      mouseListener_(new MouseListener(this)),
      threads_(new Threads(this)) {
  target_->addCommands();
  player_->addListener(components_->transportController_.get());
	typedef gui::DropTarget<Waveform> DropWave;
  DropWave* waveform = dynamic_cast<DropWave*>(components_->waveform_.get());
  waveform->dropBroadcaster()->addListener(currentFile_.get());

  widget::tree::Root* root = components_->directoryTree_.get();
  root->treeView()->dropBroadcaster()->addListener(currentFile_.get());
  root->addListener(currentFile_.get());

  components_->transportController_->addListener(target_->targetManager());

  player_->timeBroadcaster()->addListener(components_->timeController_.get());
  player_->timeBroadcaster()->addListener(waveform->timeCursor());

  player_->level()->addListener(components_->playerController_->levelListener());

  ThumbnailBuffer* thumbnailBuffer = bufferFiller_->thumbnailBuffer();
  Source *s = new FrameSource<short, 2>(thumbnailBuffer->buffer()->frames());
  player_->setSource(s);
  player_->timeBroadcaster()->addListener(currentTime_.get());
  components_->waveform_->setAudioThumbnail(thumbnailBuffer->thumbnail());

  threads_->startAll();
  currentFile_->setFile(data::get<VirtualFile>());
  window->addListener(menus_.get());

  DialogLocker::getDisableBroadcaster()->addListener(target_->targetManager());
  DialogLocker::getDisableBroadcaster()->addListener(window->application());
}

Instance::~Instance() {
  player_->setState(audio::transport::STOPPED);
  threads_->stop();
}

void Instance::startup() {
  data::editable<VirtualFile>()->onDataChange();
  components_->setActive(true);
  startUndo();
  addUndoListener(menus_.get());
}

const VirtualFile Instance::file() const {
  return currentFile_->virtualFile();
}

Samples<44100> Instance::length() const {
  return player_->length();
}

Samples<44100> Instance::time() const {
  return currentTime_->time();
}

}  // namespace slow
}  // namespace rec
