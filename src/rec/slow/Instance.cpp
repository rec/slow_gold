#include "rec/slow/Instance.h"

#include "rec/audio/Device.h"
#include "rec/audio/source/Player.h"
#include "rec/slow/Components.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Menus.h"
#include "rec/slow/Model.h"
#include "rec/slow/Target.h"
#include "rec/slow/Threads.h"

namespace rec {
namespace slow {

Instance::Instance(DocumentWindow* window)
    : window_(window),
      components_(new Components(this)),
      device_(new audio::Device),
      player_(new audio::source::Player(device_.get())),
      model_(new Model(this)),
      menus_(new Menus(this)),
      target_(new Target(this)),
      listeners_(new Listeners(this)),
      threads_(new Threads(this)) {
  target_->addCommands();
  threads_->startAll();

  model_->setFile(persist::get<VirtualFile>());
}

Instance::~Instance() {
  player_->setState(audio::transport::STOPPED);
  threads_->stop();
}

}  // namespace slow
}  // namespace rec
