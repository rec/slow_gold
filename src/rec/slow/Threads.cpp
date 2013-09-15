#include "rec/slow/Threads.h"

#include "rec/audio/source/Player.h"
#include "rec/data/Data.h"
#include "rec/data/DataCenter.h"
#include "rec/data/DataUpdater.h"
#include "rec/gui/GuiWriteable.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/Threads.h"
#include "rec/util/STL.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/util/thread/ThreadList.h"
#include "rec/widget/tree/Directory.h"
#include "rec/widget/tree/Root.h"

namespace rec {
namespace slow {

static const bool USE_NEW_STYLE = false;

using namespace rec::audio::source;
using namespace rec::audio::stretch;
using namespace rec::util::thread;

namespace {

const int THREAD_STOP_PERIOD = 2500;
const int BUFFER_FILL_CHUNK = 256;

struct Period {
  enum Enum {
    DIRECTORY = 1000,
    NAVIGATOR = 1001,
    WRITE_GUI = 201,
    WRITE_DATA = 1003,
    UPDATE_DATA = 51,
    TIMER = 101,
    CALLBACK_QUEUE = 49,
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
    CALLBACK_QUEUE = 4,
  };
};

int navigator(Instance*) {
  getInstance()->components_->directoryTree_->checkVolumes();
  return Period::NAVIGATOR;
}

int writeGui(Instance*) {
  MessageManagerLock l(getInstance()->threads_->guiThread());
  if (!l.lockWasGained())
    return DONE;
  getInstance()->updateGui();
  return Period::WRITE_GUI;
}

int writeData(Instance*) {
  data::getDataCenter().updater_->write();
  return Period::WRITE_DATA;
}

int updateData(Instance* i) {
  MessageManagerLock l(getInstance()->threads_->updateThread());
  if (!l.lockWasGained())
    return DONE;
  data::getDataCenter().updater_->update();
  return Period::UPDATE_DATA;
}

thread::Result directory(Instance*) {
  return getInstance()->components_->directoryTree_->run() ?
    thread::YIELD : static_cast<thread::Result>(Period::DIRECTORY);
}

int timer(Instance*) {
  getInstance()->player_->timer()->broadcastTime();
  return Period::TIMER;
}

}  // namespace

struct Threads::ThreadList {
  ThreadList() : guiThread_(nullptr), updateThread_(nullptr) {}
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

  Thread* guiThread_;
  Thread* timerThread_;
  Thread* updateThread_;
};

Threads::Threads() : threads_(new ThreadList) {
}

Threads::~Threads() {}

Thread* Threads::guiThread() {
  return threads_->guiThread_;
}

Thread* Threads::updateThread() {
  return threads_->updateThread_;
}

Thread* Threads::timerThread() {
  return threads_->timerThread_;
}

template <typename Operator>
Thread* Threads::start(Operator op, const String& name, int priority) {
  Thread* thread = thread::makeLooper(name, op, getInstance()).release();
  if (priority)
    thread->setPriority(priority);
  thread->startThread();
  threads_->threads_.push_back(thread);
  return thread;
}

void Threads::stop() {
  Lock l(lock_);
  threads_->stop();
}

void Threads::clean() {
  Lock l(lock_);
  threads_->clean();
}

namespace {

int navigator2(Thread*) {
  getInstance()->components_->directoryTree_->checkVolumes();
  return Period::NAVIGATOR;
}

int writeGui2(Thread*) {
  MessageManagerLock l(getInstance()->threads_->guiThread());
  if (!l.lockWasGained())
    return DONE;
  getInstance()->updateGui();
  return Period::WRITE_GUI;
}

int writeData2(Thread*) {
  data::getDataCenter().updater_->write();
  return Period::WRITE_DATA;
}

int updateData2(Thread*) {
  MessageManagerLock l(getInstance()->threads_->updateThread());
  if (!l.lockWasGained())
    return DONE;
  data::getDataCenter().updater_->update();
  return Period::UPDATE_DATA;
}

int directory2(Thread*) {
  return getInstance()->components_->directoryTree_->run() ?
    thread::YIELD : static_cast<thread::Result>(Period::DIRECTORY);
}

int timer2(Thread*) {
  getInstance()->player_->timer()->broadcastTime();
  return Period::TIMER;
}

thread::LooperDesc LOOPERS[] = {
  {"directory", 3, 1000, directory2},
  {"navigator", 2, 1001, navigator2},
  {"update data", 4, 51, updateData2},
  {"write GUI", 4, 201, writeGui2},
  {"write data", 4, 1003, writeData2},
  {"timer", 4, 101, timer2},
};

}  // namespace

void Threads::start() {
  if (USE_NEW_STYLE) {
    threads2_ = thread::newLooperList(std::begin(LOOPERS), std::end(LOOPERS));
  } else {
    start(&navigator, "Navigator", Priority::NAVIGATOR);
    start(&directory, "Directory", Priority::DIRECTORY);
    start(&writeData, "writeData", Priority::WRITE_DATA);

    threads_->guiThread_ =
      start(&writeGui, "writeGUI", Priority::WRITE_GUI);
    threads_->updateThread_
      = start(&updateData, "updateData", Priority::UPDATE_DATA);
    threads_->timerThread_ =
      start(&timer, "timer", Priority::TIMER);
  }
}

}  // namespace slow
}  // namespace rec
