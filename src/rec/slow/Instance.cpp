#include "rec/slow/Instance.h"

#include "rec/audio/Device.h"
#include "rec/audio/source/Player.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/Menus.h"
#include "rec/slow/Model.h"
#include "rec/slow/MouseListener.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/Target.h"
#include "rec/slow/Threads.h"
#include "rec/widget/waveform/Cursor.h"

namespace rec {
namespace slow {

Instance::Instance(SlowWindow* window)
    : window_(window),
      components_(new Components(this)),
      device_(new audio::Device),
      player_(new audio::source::Player(device_.get())),
      currentFile_(new CurrentFile(this)),
      model_(new Model(this)),
      menus_(new Menus(this)),
      target_(new Target(this)),
      mouseListener_(new MouseListener(this)),
      threads_(new Threads(this)) {
  target_->addCommands();
  player_->addListener(&components_->transportController_);

  WaveformComp* waveform = &components_->waveform_;
  waveform->dropBroadcaster()->addListener(model_.get());

  widget::tree::Root* root = &components_->directoryTree_;
  root->treeView()->dropBroadcaster()->addListener(model_.get());
  root->addListener(model_.get());

  components_->transportController_.addListener(target_->targetManager());

  player_->timeBroadcaster()->addListener(&components_->timeController_);
  player_->timeBroadcaster()->addListener(waveform->timeCursor());

  player_->level()->addListener(components_->playerController_.levelListener());

  threads_->startAll();
}

Instance::~Instance() {
  player_->setState(audio::transport::STOPPED);
  threads_->stop();
}

void Instance::startup() {
  model_->setFile(data::get<VirtualFile>());
}

const VirtualFile Instance::file() const {
  return currentFile_->virtualFile();
}

}  // namespace slow
}  // namespace rec
