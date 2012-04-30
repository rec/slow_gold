#include "rec/slow/Threads.h"

#include "rec/audio/source/Player.h"
#include "rec/data/Data.h"
#include "rec/data/DataCenter.h"
#include "rec/data/DataUpdater.h"
#include "rec/gui/GuiWriteable.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Menus.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/Threads.h"
#include "rec/util/STL.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/widget/tree/Directory.h"
#include "rec/widget/tree/Root.h"

namespace rec {
namespace slow {

// Skin

using namespace rec::audio::source;
using namespace rec::audio::stretch;
using namespace rec::util::thread;

namespace {

const int THREAD_STOP_PERIOD = 20000;
const int BUFFER_FILL_CHUNK = 256;

struct Period {
  enum Enum {
    DIRECTORY = 1000,
    NAVIGATOR = 1001,
    WRITE_GUI = 201,
    WRITE_DATA = 1003,
    UPDATE_DATA = 51,
    TIMER = 101,
    BROADCAST = 49,
  };
};

struct Priority {
  enum Enum {
    DIRECTORY = 3,
    NAVIGATOR = 2,
    WRITE_GUI = 4,
    WRITE_DATA = 4,
    UPDATE_DATA = 4,
    TIMER = 4,
    BROADCAST = 4,
  };
};

int navigator(Instance* i) {
  i->components_->directoryTree_->checkVolumes();
  return Period::NAVIGATOR;
}

int writeGui(Instance* i) {
  i->updateGui();
  return Period::WRITE_GUI;
}

int writeData(Instance*) {
  data::getDataCenter().updater_->write();
  return Period::WRITE_DATA;
}

int updateData(Instance*) {
  data::getDataCenter().updater_->update();
  return Period::UPDATE_DATA;
}

thread::Result directory(Instance* i) {
  return i->components_->directoryTree_->run() ?
    thread::YIELD : static_cast<thread::Result>(Period::DIRECTORY);
}

int timer(Instance* i) {
  i->player_->timer()->broadcastTime();
  return Period::TIMER;
}

}  // namespace

struct Threads::ThreadList {
  ~ThreadList() {
    stop();
    stl::deletePointers(&threads_);
  }

  void stop() {
    for (uint i = 0; i < threads_.size(); ++i)
      threads_[i]->stopThread(THREAD_STOP_PERIOD);
  }

  void clean() {
    for (uint i = 0; i < threads_.size(); ++i) {
      if (!threads_[i]->isThreadRunning()) {
        delete threads_[i];
        threads_[i] = threads_.back();
        threads_.pop_back();
      }
    }
  }

  vector<Thread*> threads_;
};

Threads::Threads(Instance* i) : HasInstance(i), threadList_(new ThreadList) {}
Threads::~Threads() {}

template <typename Operator>
Thread* Threads::start(Operator op, const String& name, int priority) {
  Thread* thread = thread::makeLooper(name, op, instance_);
  if (priority)
    thread->setPriority(priority);
  thread->startThread();
  threadList_->threads_.push_back(thread);
  return thread;
}

void Threads::stop() {
  Lock l(lock_);
  threadList_->stop();
}

void Threads::clean() {
  Lock l(lock_);
  threadList_->clean();
}

void Threads::start() {
  start(&navigator, "Navigator", Priority::NAVIGATOR);
  start(&directory, "Directory", Priority::DIRECTORY);
  start(&writeGui, "writeGUI", Priority::WRITE_GUI);
  start(&writeData, "writeData", Priority::WRITE_DATA);
  start(&updateData, "updateData", Priority::UPDATE_DATA);
  player()->timer()->setThread(start(&timer, "timer", Priority::TIMER));
  //  callbackThread_ = startThread(
}

}  // namespace slow
}  // namespace rec
