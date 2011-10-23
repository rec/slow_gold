#include "rec/slow/Threads.h"
#include "rec/data/Data.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Listeners.h"
#include "rec/slow/Model.h"
#include "rec/slow/Threads.h"
#include "rec/util/STL.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/widget/tree/Directory.h"

namespace rec {
namespace slow {

using namespace rec::audio::source;
using namespace rec::audio::stretch;
using namespace rec::audio::util;
using namespace rec::util::thread;

static const int THREAD_STOP_PERIOD = 5000;
static const int BUFFER_FILL_CHUNK = 256;

Threads::Threads(Instance* i) : HasInstance(i),
                                fillThread_(NULL), bufferThread_(NULL) {}

Threads::~Threads() {
  stop();
  stl::deletePointers(&threads_);
}

void Threads::stop() {
  for (uint i = 0; i < threads_.size(); ++i) {
    VLOG(1) << "Stopping thread " << threads_[i]->getThreadName();
    threads_[i]->stopThread(THREAD_STOP_PERIOD);
  }
}

void Threads::clean() {
  ScopedLock l(lock_);
  for (uint i = 0; i < threads_.size(); ++i) {
    if (!threads_[i]->isThreadRunning()) {
      delete threads_[i];
      threads_[i] = threads_.back();
      threads_.pop_back();
    }
  }
}

namespace {

struct Period {
  enum Enum {
    BUFFER = 39,
    DIRECTORY = 1000,
    FILL = 40,
    NAVIGATOR = 1001,
    PARAMETER = 41
  };
};


struct Priority {
  enum Enum {
    BUFFER = 3,
    DIRECTORY = 3,
    FILL = 5,
    NAVIGATOR = 2,
    PARAMETER = 5
  };
};

int navigator(Instance* i) {
  i->components_->directoryTree_.checkVolumes();
  return Period::NAVIGATOR;
}

thread::Result fill(Instance* i) {
  return i->model_->fillOnce();
}

thread::Result directory(Instance* i) {
  return i->components_->directoryTree_.run() ?
    thread::YIELD : static_cast<thread::Result>(Period::DIRECTORY);
}

}  // namespace

void Threads::startAll() {
  start(&navigator, "Navigator", Priority::NAVIGATOR);
  fillThread_ = start(&fill, "Fill", Priority::FILL);
  start(&directory, "Directory", Priority::DIRECTORY);
}

}  // namespace slow
}  // namespace rec
