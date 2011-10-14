#include "rec/data/UndoQueue.h"
#include "rec/data/Action.pb.h"
#include "rec/data/Editable.h"
#include "rec/util/STL.h"
#include "rec/util/file/LogFile.h"

#include "rec/data/proto/Proto.h"

namespace rec {
namespace data {

UndoQueue::UndoQueue(const File& file)
    : logfile_(new file::Output(file)), writtenTo_(0), undoes_(0) {
}

UndoQueue::~UndoQueue() {
  Lock l(lock_);
  write();
  stl::deletePointers(&events_);
}

void UndoQueue::add(Action* event) {
  Lock l(lock_);
  if (undoes_) {
    if (undoes_ > 1)
      events_.resize(events_.size() - undoes_ + 1);
    events_.back() = event;
    undoes_ = 0;
  } else {
    events_.push_back(event);
  }
}

void doAction(Editable* editable, Action* action, bool isUndo) {
  const OperationList& ops = isUndo ? action->undo() : action->operations();
  ptr<OperationList> res(editable->applyOperationList(ops));
  if (isUndo && !action->operations().operation_size() && res->operation_size())
    action->mutable_operations()->CopyFrom(*res);
}

void UndoQueue::undo(Editable* editable) {
  if (undoable())
    doAction(editable, events_[events_.size() - ++undoes_], true);
}

void UndoQueue::redo(Editable* editable) {
  if (undoes_)
    doAction(editable, events_[events_.size() - undoes_--], false);
}

bool UndoQueue::write() {
  ptr<ActionList> events;
  {
    Lock l(lock_);
    int size = events_.size();
    if (writtenTo_ == size)
      return false;

    events.reset(new ActionList(events_.begin() + writtenTo_, events_.end()));
    writtenTo_ = size;
  }

  for (ActionList::iterator i = events->begin(); i != events->end(); ++i)
    logfile_->write(**i);

  return true;
}

void UndoQueue::add(Editable* e, const OperationQueue& q) {
  ptr<Action> action(new Action);
  action->mutable_file()->CopyFrom(e->virtualFile());
  action->set_type_name(e->getTypeName());
  typedef google::protobuf::RepeatedPtrField<Operation> RepeatedOperation;
  RepeatedOperation* op = action->mutable_undo()->mutable_operation();
  for (int i = q.size() - 1; i >=0; --i)
    op->MergeFrom(q[i]->operation());

  add(action.transfer());
}

}  // namespace data
}  // namespace rec
