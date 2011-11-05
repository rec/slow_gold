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
  stl::deletePointers(&actions_);
}

static Action* makeAction(Editable* e, const OperationList& command,
                          const OperationList& undo) {
  ptr<Action> action(new Action);
  action->mutable_file()->CopyFrom(e->virtualFile());
  action->set_type_name(e->getTypeName());

  typedef google::protobuf::RepeatedPtrField<Operation> RepeatedOperation;
  RepeatedOperation* op = action->mutable_undo()->mutable_operation();
  for (int i = undo.size() - 1; i >= 0; --i)
    if (undo[i])
      op->MergeFrom(undo[i]->operation());

  op = action->mutable_operations()->mutable_operation();
  for (int i = command.size() - 1; i >= 0; --i) {
    if (command[i])  // TODO: these should be filtered earlier.
      op->MergeFrom(command[i]->operation());
  }

  return action.transfer();
}

void UndoQueue::add(Editable* editable, const OperationList& command,
                    const OperationList& undo) {
  Lock l(lock_);
  if (!enabled_)
    return;

  ptr<Action> action(makeAction(editable, command, undo));
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
  ptr<ActionList> events;
  {
    Lock l(lock_);
    int size = actions_.size();
    if (writtenTo_ == size)
      return false;

    events.reset(new ActionList(actions_.begin() + writtenTo_, actions_.end()));
    writtenTo_ = size;
  }

  for (ActionList::iterator i = events->begin(); i != events->end(); ++i) {
    logfile_->write(**i);
    logfile_->flush();
  }

  return true;
}


}  // namespace data
}  // namespace rec
