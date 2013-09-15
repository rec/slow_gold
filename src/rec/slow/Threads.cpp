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
#include "rec/widget/tree/Directory.h"
#include "rec/widget/tree/Root.h"

namespace rec {
namespace slow {

using namespace rec::audio::source;
using namespace rec::audio::stretch;
using namespace rec::util::thread;

namespace {

const int BUFFER_FILL_CHUNK = 256;

}  // namespace

Threads::Threads() {}
Threads::~Threads() {}

Thread* Threads::timerThread() {
  return threads_->at("timer");
}

void Threads::stop() {
  threads_->stop();
}

namespace {

int navigator(Thread*) {
  getInstance()->components_->directoryTree_->checkVolumes();
  return WAIT;
}

int writeGui(Thread* thread) {
  MessageManagerLock l(thread);
  if (!l.lockWasGained())
    return DONE;
  getInstance()->updateGui();
  return WAIT;
}

int writeData(Thread*) {
  data::getDataCenter().updater_->write();
  return WAIT;
}

int updateData(Thread* thread) {
  MessageManagerLock l(thread);
  if (!l.lockWasGained())
    return DONE;
  data::getDataCenter().updater_->update();
  return WAIT;
}

int directory(Thread*) {
  return getInstance()->components_->directoryTree_->run() ? YIELD : WAIT;
}

int timer(Thread*) {
  getInstance()->player_->timer()->broadcastTime();
  return WAIT;
}

thread::LooperDesc LOOPERS[] = {
  {"directory", 3, 1000, directory},
  {"navigator", 2, 1001, navigator},
  {"update data", 4, 51, updateData},
  {"write GUI", 4, 201, writeGui},
  {"write data", 4, 1003, writeData},
  {"timer", 4, 101, timer},
};

}  // namespace

void Threads::start() {
  threads_ = thread::newLooperList(std::begin(LOOPERS), std::end(LOOPERS));
  threads_->start();
}

}  // namespace slow
}  // namespace rec
