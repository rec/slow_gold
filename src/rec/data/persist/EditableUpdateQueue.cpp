#include "rec/data/persist/EditableUpdateQueue.h"
#include "rec/app/Files.h"
#include "rec/data/commands/UndoQueue.h"
#include "rec/data/persist/EditableFactory.h"
#include "rec/data/persist/TypedEditable.h"
#include "rec/util/STL.h"
#include "rec/util/thread/MakeThread.h"

namespace rec {
namespace persist {

using data::UntypedEditable;

EditableUpdateQueue::EditableUpdateQueue()
    : factory_(new EditableFactory()),
      undo_(new data::commands::UndoQueue(app::getAppFile("UndoQueue.Action"))) {
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
void EditableUpdateQueue::doUpdate(UntypedEditable* data) {
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

// static
void EditableUpdateQueue::addToUndoQueue(UntypedEditable* e,
                                         data::OperationQueue* q) {
  instance_->undo_->add(e, q);
}

template <typename DataSet, typename Method>
bool operateOn(DataSet *from, DataSet *to, CriticalSection* lock, Method m) {
  DataSet ds;
  {
    ScopedLock l(*lock);
    if (from->empty())
      return true;
    stl::moveTo(from, &ds);
  }

  for (typename DataSet::iterator i = ds.begin(); i != ds.end(); ++i)
    ((*i)->*m)();

  stl::moveTo(&ds, to);
  return false;
}

bool EditableUpdateQueue::update() {
  bool res = !running() ||
    operateOn(&updateData_, &writeData_, &lock_, &UntypedEditable::update) ||
    !running();
  if (res)
    writeThread_->notify();
  return res;
}

bool EditableUpdateQueue::write() {
  if (!running())
    return true;

  DataSet ds;
  bool res = operateOn(&writeData_, &ds, &lock_, &UntypedEditable::writeToFile);
  stl::deletePointers(&ds);
  return res || !running();
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
