#include "rec/data/UndoQueue.h"
#include "rec/data/Action.pb.h"
#include "rec/data/Editable.h"
#include "rec/util/STL.h"
#include "rec/util/file/LogFile.h"

namespace rec {
namespace data {

UndoQueue::UndoQueue(const File& file)
    : logfile_(new file::Output(file)), writtenTo_(0), undoes_(0) {
}

UndoQueue::~UndoQueue() {
  Lock l(lock_);
  write();
  stl::deletePointers(&actions_);
}

static Action* makeAction(Editable* e, const OperationList& q) {
  ptr<Action> action(new Action);
  action->mutable_file()->CopyFrom(e->virtualFile());
  action->set_type_name(e->getTypeName());
  typedef google::protobuf::RepeatedPtrField<Operation> RepeatedOperation;
  RepeatedOperation* op = action->mutable_undo()->mutable_operation();
  for (int i = q.size() - 1; i >=0; --i)
    op->MergeFrom(q[i]->operation());

  return action.transfer();
}

void UndoQueue::add(Editable* editable, const OperationList& q) {
  ptr<Action> action(makeAction(editable, q));
  Lock l(lock_);
  if (undoes_) {
    if (undoes_ > 1) {
      actions_.resize(undoable() + 1);
      editables_.resize(actions_.size());
    }
    actions_.back() = action.transfer();
    editables_.back() = editable;
    undoes_ = 0;
  } else {
    actions_.push_back(action.transfer());
    editables_.push_back(editable);
  }
}

void UndoQueue::executeTop(bool isUndo) {
  int top = undoable();
  Editable* editable = editables_[top];
  Action* action = actions_[top];
  const Operations& ops = isUndo ? action->undo() : action->operations();
  ptr<Operations> res(editable->applyOperations(ops));
#if 0
  if (isUndo && !action->operations().operation_size() && res->operation_size())
    action->mutable_operations()->CopyFrom(*res);
#endif
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
  ptr<ActionList> events;
  {
    Lock l(lock_);
    int size = actions_.size();
    if (writtenTo_ == size)
      return false;

    events.reset(new ActionList(actions_.begin() + writtenTo_, actions_.end()));
    writtenTo_ = size;
  }

  for (ActionList::iterator i = events->begin(); i != events->end(); ++i)
    logfile_->write(**i);

  return true;
}


}  // namespace data
}  // namespace rec
