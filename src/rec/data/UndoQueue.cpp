#include "rec/data/UndoQueue.h"
#include "rec/data/Action.pb.h"
#include "rec/data/Editable.h"
#include "rec/util/STL.h"
#include "rec/util/file/LogFile.h"

namespace rec {
namespace data {

using file::Output;

UndoQueue::UndoQueue(const File& file)
    : logfile_(new Output(file, copy::READABLE)),
      writtenTo_(0),
      undoes_(0),
      enabled_(false) {
}

UndoQueue::~UndoQueue() {
  Lock l(lock_);
  write();
  stl::deletePointers(&queue_);
}

static Action* makeAction(Editable* e, const Operations& operations,
                          const Operations& undo) {
  ptr<Action> action(new Action);
  action->mutable_file()->CopyFrom(e->virtualFile());
  action->set_type_name(e->getTypeName());

  action->mutable_undo()->MergeFrom(undo);
  action->mutable_operations()->MergeFrom(operations);

  return action.transfer();
}

void UndoQueue::add(Editable* editable, const Operations& operations,
                    const Operations& undo) {
  Lock l(lock_);
  if (!enabled_)
    return;

  ptr<Action> action(makeAction(editable, operations, undo));
  if (undoes_) {
    if (undoes_ > 1) {
      queue_.resize(undoable() + 1);
      editables_.resize(queue_.size());
    }
    queue_.back() = action.transfer();
    editables_.back() = editable;
    undoes_ = 0;
  } else {
    queue_.push_back(action.transfer());
    editables_.push_back(editable);
  }
}

void UndoQueue::executeTop(bool isUndo) {
  int top = undoable();
  Editable* editable = editables_[top];
  Action* action = queue_[top];
  const Operations& ops = isUndo ? action->undo() : action->operations();
  DCHECK(false) << "Need to apply without adding an undo to the queue";
  ptr<Operations>(editable->applyOperations(ops));
}

void UndoQueue::undo() {
  if (undoable()) {
    ++undoes_;
    executeTop(true);
  }
}

void UndoQueue::redo() {
  if (undoes_) {
    executeTop(false);
    --undoes_;
  }
}

bool UndoQueue::write() {
  ptr<ActionQueue> events;
  {
    Lock l(lock_);
    int size = queue_.size();
    if (writtenTo_ == size)
      return false;

    events.reset(new ActionQueue(queue_.begin() + writtenTo_, queue_.end()));
    writtenTo_ = size;
  }

  for (ActionQueue::iterator i = events->begin(); i != events->end(); ++i) {
    Action action(**i);
    action.mutable_operations()->Clear();
    logfile_->write(action);
    logfile_->flush();
  }

  return true;
}


}  // namespace data
}  // namespace rec
