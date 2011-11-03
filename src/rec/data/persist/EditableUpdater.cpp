#include <set>

#include "rec/data/persist/EditableUpdater.h"

#include "rec/app/Files.h"
#include "rec/data/EditableFactory.h"
#include "rec/data/persist/TypedEditable.h"
#include "rec/util/DefaultRegistry.h"
#include "rec/util/STL.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/util/thread/Trash.h"

namespace rec {
namespace data {

namespace {

struct ThreadDesc {
  int priority_;
  int period_;
  const char* name_;
};

ThreadDesc updateDesc = {5, 40, "Editable::Update"};
ThreadDesc writeDesc = {5, 100, "Editable::Write"};

template <typename Method>
Thread* makeLoop(const ThreadDesc& d, EditableUpdater* upd, Method method) {
  thread_ptr<Thread> t(thread::makeLoop(d.period_, d.name_, upd, method));

  t->setPriority(d.priority_);
  t->startThread();

  return t.transfer();
}

static bool lockedCopy(EditableSet* from, EditableSet* to, CriticalSection* lock) {
  ScopedLock l(*lock);
  bool hasData = !from->empty();
  if (hasData)
    stl::moveTo(from, to);

  return hasData;
}

}  // namespace

EditableUpdater::EditableUpdater(DefaultRegistry* registry)
    : undoQueue_(app::getAppFile("UndoQueue.Action")),
      defaultRegistry_(registry),
      updateThread_(makeLoop(updateDesc, this, &EditableUpdater::update)),
      writeThread_(makeLoop(writeDesc, this, &EditableUpdater::write)) {
}

EditableUpdater::~EditableUpdater() {
  writeThread_->stopThread(1000);
  updateThread_->stopThread(1000);
  stl::deleteMapPointers(&map_);
}

// A piece of data got new information!
void EditableUpdater::needsUpdate(UntypedEditable* data) {
  {
    ScopedLock l(lock_);
    updateData_.insert(data);
  }
  updateThread_->notify();
}

bool EditableUpdater::update() {
  EditableSet ds, writeable;
  if (!lockedCopy(&updateData_, &ds, &lock_))
    return false;

  for (EditableSet::iterator i = ds.begin(); i != ds.end(); ++i) {
    if ((*i)->update())
      writeable.insert(*i);
  }

  lockedCopy(&writeable, &writeData_, &lock_);
  writeThread_->notify();

  return true;
}

bool EditableUpdater::write() {
  EditableSet ds;
  if (!lockedCopy(&writeData_, &ds, &lock_))
    return false;

  for (EditableSet::iterator i = ds.begin(); i != ds.end(); ++i)
    (*i)->writeToFile();

  return true;
}

void EditableUpdater::start(DefaultRegistry* r) {
  CHECK(!instance_);
  instance_ = new EditableUpdater(r);
}

void EditableUpdater::stop() {
  delete instance_;
  instance_ = NULL;
}

EditableUpdater* EditableUpdater::instance_ = NULL;

namespace {

EditableUpdater* instance() { return EditableUpdater::instance(); }
UndoQueue* undoQueue() { return instance()->undoQueue(); }

}  // namespace

void addToUndoQueue(UntypedEditable* u, const OperationList& command,
                    const OperationList& undo) {
  return undoQueue()->add(u, command, undo);
}

void needsUpdate(UntypedEditable* e) { return instance()->needsUpdate(e); }
EditableMap* editableMap()           { return instance()->map(); }
CriticalSection* editableMapLock()   { return instance()->lock(); }
const DefaultRegistry& defaultRegistry() { return instance()->defaultRegistry(); }

void start(DefaultRegistry* r) { EditableUpdater::start(r); }
void stop() { EditableUpdater::stop(); }

}  // namespace data
}  // namespace rec
