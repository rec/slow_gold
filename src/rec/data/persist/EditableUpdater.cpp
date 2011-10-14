#include <set>

#include "rec/app/Files.h"
#include "rec/data/Editable.h"
#include "rec/data/UndoQueue.h"
#include "rec/data/persist/EditableFactory.h"
#include "rec/data/persist/TypedEditable.h"
#include "rec/util/STL.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/util/thread/Trash.h"

namespace rec {
namespace data {

using commands::UndoQueue;

namespace {

typedef std::set<data::UntypedEditable*> DataSet;

struct ThreadDesc {
  int priority_;
  int period_;
  const char* name_;
};

ThreadDesc updateDesc = {5, 40, "Editable::Update"};
ThreadDesc writeDesc = {5, 100, "Editable::Write"};

struct EditableUpdater  {
  template <typename Method>
  Thread* makeLoop(const ThreadDesc& d, Method method) {
    thread_ptr<Thread> t(thread::makeLoop(d.period_, d.name_, this, method));
    t->setPriority(d.priority_);
    t->startThread();
    return t.transfer();
  }

  EditableUpdater() : undoQueue_(app::getAppFile("UndoQueue.Action")) {
    updateThread_.reset(makeLoop(updateDesc, &EditableUpdater::update));
    writeThread_.reset(makeLoop(writeDesc, &EditableUpdater::write));
  }

  ~EditableUpdater() {
    writeThread_->stopThread(1000);
    updateThread_->stopThread(1000);
  }

  // A piece of data got new information!
  void needsUpdate(UntypedEditable* data) {
    {
      ScopedLock l(lock_);
      updateData_.insert(data);
    }
    updateThread_->notify();
  }

  bool lockedCopy(DataSet* from, DataSet* to) {
    ScopedLock l(lock_);
    bool hasData = !from->empty();
    if (hasData)
      stl::moveTo(from, to);

    return hasData;
  }

  bool update() {
    DataSet ds;
    bool hasData = lockedCopy(&updateData_, &ds);
    if (hasData) {
      for (DataSet::iterator i = ds.begin(); i != ds.end(); ++i)
        (*i)->update();

      lockedCopy(&ds, &writeData_);
      writeThread_->notify();
    }
    return !hasData;
  }

  bool write() {
    DataSet ds;
    bool hasData = lockedCopy(&writeData_, &ds);
    if (hasData) {
      for (DataSet::iterator i = ds.begin(); i != ds.end(); ++i) {
        (*i)->writeToFile();
        delete *i;
      }
    }
    return !hasData;
  }

  static void start() {
    CHECK(!instance_);
    instance_ = new EditableUpdater();
  }

  static void stop() {
    delete instance_;
    instance_ = NULL;
  }

  EditableMap* map() { return &map_; }
  CriticalSection* lock() { return &lock_; }

  CriticalSection lock_;

  DataSet updateData_;
  DataSet writeData_;
  EditableMap map_;

  thread_ptr<Thread> updateThread_;
  thread_ptr<Thread> writeThread_;
  UndoQueue undoQueue_;

  static EditableUpdater* instance_;

  DISALLOW_COPY_AND_ASSIGN(EditableUpdater);
};


EditableUpdater* EditableUpdater::instance_ = NULL;
EditableUpdater* instance() { return EditableUpdater::instance_; }
UndoQueue* undoQueue() { return &EditableUpdater::instance_->undoQueue_; }

}  // namespace

void needsUpdate(UntypedEditable* e) {
  return instance()->needsUpdate(e);
}

void addToUndoQueue(UntypedEditable* u, const OperationQueue& q) {
  return undoQueue()->add(u, q);
}

EditableMap* editableMap() {
  return &instance()->map_;
}

CriticalSection* editableMapLock() {
	return &instance()->lock_;
}

void start() { EditableUpdater::start(); }
void stop() { EditableUpdater::stop(); }

}  // namespace data

namespace util {

// How many commands have been undone?
int undoes() {
  return data::undoQueue()->undoes();
}

// How many commands can be undone?
int undoable() {
  return data::undoQueue()->undoable();
}

void undo() {
}

void redo() {
}

}  // namespace util
}  // namespace rec
