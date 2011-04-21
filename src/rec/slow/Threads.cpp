#include "rec/slow/Threads.h"
#include "rec/slow/Instance.h"
#include "rec/util/thread/MakeThread.h"


namespace rec {
namespace slow {

static const int CLOCK_PERIOD = 10;

Threads::Threads(Instance* i) :
    instance_(i),
    clock_(thread::makeLoop(CLOCK_PERIOD, "Clock", this, &Threads::clock)) {
  clock_->startThread();
}

void Threads::clock() {
  instance_->listeners_(instance_->player_.getNextReadPosition());
}

}  // namespace slow
}  // namespace rec
