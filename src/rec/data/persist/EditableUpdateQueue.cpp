#include "rec/data/persist/EditableUpdateQueue.h"
#include "rec/data/persist/EditableFactory.h"
#include "rec/data/persist/TypedEditable.h"
#include "rec/util/STL.h"
#include "rec/util/thread/MakeThread.h"

namespace rec {
namespace persist {

using data::UntypedEditable;

EditableUpdateQueue::EditableUpdateQueue() : factory_(new EditableFactory()) {
  updateThread_.reset(thread::makeLoop(UPDATE_PERIOD, "App::update",
                                       this, &EditableUpdateQueue::update));
  updateThread_->setPriority(UPDATE_PRIORITY);

  writeThread_.reset(thread::makeLoop(WRITE_PERIOD, "App::write",
                                       this, &EditableUpdateQueue::write));
  writeThread_->setPriority(WRITE_PRIORITY);
  updateThread_->startThread();
  writeThread_->startThread();
}

EditableUpdateQueue::~EditableUpdateQueue() {
  writeThread_->stopThread(1000);
  updateThread_->stopThread(1000);
}

// A piece of data got new information!
void EditableUpdateQueue::needsUpdate(UntypedEditable* data) {
  {
    ScopedLock l(lock_);
    updateData_.insert(data);
  }
  updateThread_->notify();
}

bool EditableUpdateQueue::running() const {
	return writeThread_ && updateThread_ &&
    !(writeThread_->threadShouldExit() || writeThread_->threadShouldExit());
}

template <typename Container>
bool lockedEmpty(const Container &c, CriticalSection* lock) {
  ScopedLock l(*lock);
  return c.empty();
}

template <typename Container>
void extendAndClear(Container *from, Container *to, CriticalSection* lock) {
  ScopedLock l(*lock);
  if (to->empty()) {
    to->swap(*from);
  } else {
    to->insert(from->begin(), from->end());
    to->clear();
  }
}

bool EditableUpdateQueue::update() {
  if (lockedEmpty(updateData_, &lock_) || !running())
    return true;

  DataSet updates;
  extendAndClear(&updateData_, &updates, &lock_);
  for (DataSet::iterator i = updates.begin(); i != updates.end() && running(); ++i)
    (*i)->update();

  extendAndClear(&updates, &writeData_, &lock_);
  if (running())
    writeThread_->notify();
  return true;
}

bool EditableUpdateQueue::write() {
  if (lockedEmpty(writeData_, &lock_))
    return true;

  DataSet writes;
  extendAndClear(&writeData_, &writes, &lock_);

  for (DataSet::iterator i = writes.begin(); i != writes.end() && running(); ++i)
    (*i)->writeToFile();
  return true;
}

void EditableUpdateQueue::start() {
  CHECK(!instance_);
  instance_ = new EditableUpdateQueue();
}

void EditableUpdateQueue::stop() {
  delete instance_;
  instance_ = NULL;
}

EditableUpdateQueue* EditableUpdateQueue::instance_ = NULL;

EditableFactory* getEditableFactory() {
  return EditableUpdateQueue::getFactory();
}

}  // namespace persist
}  // namespace rec
