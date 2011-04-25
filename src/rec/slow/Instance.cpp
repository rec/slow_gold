#include "rec/slow/Instance.h"

#include "rec/audio/Device.h"
#include "rec/audio/source/Player.h"
#include "rec/slow/Menus.h"
#include "rec/slow/PersistentData.h"
#include "rec/slow/Threads.h"
#include "rec/slow/Target.h"

namespace rec {
namespace slow {

Instance::Instance()
  : components_(new Components(this)),
    device_(new audio::Device()),
    menus_(new Menus(this)),
    data_(new PersistentData()),
    player_(new Player(device_.get())),
    target_(new Target(this)),
    listeners_(new Listeners(this)),
    threads_(new Threads(this)) {
  threads_->startAll();
}


Instance::~Instance() {
  threads_->stop();
}

}  // namespace slow
}  // namespace rec
