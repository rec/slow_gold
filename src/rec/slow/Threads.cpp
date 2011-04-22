#include "rec/slow/Threads.h"
#include "rec/slow/Instance.h"
#include "rec/util/thread/MakeThread.h"


namespace rec {
namespace slow {

static const int CLOCK_PERIOD = 10;

Threads::Threads(Instance* i) :
    instance_(i),
    clock_(thread::makeLoop(CLOCK_PERIOD, "Clock", this, &Threads::clock)),
    directory_(&instance_->components_.directoryTree_) {
  clock_->startThread();
  directory_->startThread();
}

void Threads::clock() {
  instance_->listeners_(instance_->player_.getNextReadPosition());
}

void Threads::stop() {
  directory_->stopThread(5000);
  clock_->stopThread(5000);
}

}  // namespace slow
}  // namespace rec
