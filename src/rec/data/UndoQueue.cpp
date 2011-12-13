#include "rec/data/UndoQueue.h"
#include "rec/data/Action.pb.h"
#include "rec/data/Editable.h"
#include "rec/data/Grouper.h"
#include "rec/util/STL.h"
#include "rec/util/file/LogFile.h"

namespace rec {
namespace data {

static const bool DELETE_UNDO_QUEUE = true;

using file::Output;

UndoQueue::UndoQueue(const File& file, ActionGrouper grouper, CanGroup can)
    : writtenTo_(0),
      undoes_(0),
      executedSize_(0),
      preUndoSize_(0),
      running_(false),
      grouper_(grouper),
      canGroup_(can) {
  if (DELETE_UNDO_QUEUE)
    file.deleteFile();
  logfile_.reset(new Output(file));
  if (!grouper_)
    grouper_ = &actionGrouper;
  if (canGroup_)
    canGroup_ = canGroup;
}

UndoQueue::~UndoQueue() {
  Lock l(lock_);

  write(true);
  stl::deletePointers(&queue_);
}

static Action* makeAction(Action::Type type) {
  ptr<Action> action(new Action);
  action->set_type(type);
  return action.transfer();
}

void UndoQueue::add(Editable* e, const Operations& operations, const Operations& undo) {
  {
    Lock l(lock_);
    if (!(running_ && operations.undoable()))
      return;
  }

#if 1
  DLOG(INFO) << "add: " << e->toString() << "\n"
             << operations.ShortDebugString() << "\n"
             << undo.ShortDebugString();
#endif

  ptr<Action> action(makeAction(Action::OPERATION));
  action->mutable_file()->CopyFrom(e->virtualFile());
  action->set_type_name(e->getTypeName());
  action->set_timestamp(juce::Time::currentTimeMillis());

  action->mutable_operations()->MergeFrom(operations);
  action->mutable_undo()->MergeFrom(undo);

  if (queue_.empty() || !grouper_(*action, queue_.back(), e)) {
    queue_.push_back(action.transfer());
    editables_.push_back(e);
    undoes_ = 0;
    preUndoSize_ = executedSize_ = queue_.size();
  }
  broadcast(None());

  // DLOG(INFO) << "undoable:" << undoable() << ", undoes:" << undoes();
}

void UndoQueue::redoOrUndo(Action::Type type) {
  DLOG(INFO) << "undoable:" << undoable() << ", undoes:" << undoes();
  DCHECK(type == Action::UNDO || type == Action::REDO);
  int td = (type == Action::REDO) ? 1 : -1;

  int position = executedSize_ + td;
  if (type == Action::REDO)
    position--;

  if (position < 0 || position >= preUndoSize_) {
    LOG(DFATAL) << "CommandIDEncoder is out of range at " << position
               << ", " << preUndoSize_;
    return;
  }

  Action* action = queue_[position];
  int pos = position;
  Action::Type t = type;
  while (action->type() != Action::OPERATION) {
    switch (action->type()) {
     case Action::UNDO:
      t = (t == Action::UNDO) ? Action::REDO : Action::UNDO;
     case Action::REDO:
      pos = action->undo_index();
      action = queue_[pos];
      continue;

     case Action::START_OF_SESSION:
     case Action::END_OF_SESSION:
     default:
      LOG(DFATAL) << "Tried to " << type << " a " << action->type();
      return;
    }
  }

  Editable* editable = editables_[pos];
  if (!editable) {
    LOG(DFATAL) << "No editable for " << type;
    return;
  }

  editable->applyOperations((t == Action::UNDO) ? action->undo() :
                            action->operations());

  ptr<Action> newAction(makeAction(type));
  newAction->set_undo_index(position);
  queue_.push_back(newAction.transfer());
  editables_.push_back(NULL);

  undoes_ -= td;
  executedSize_ += td;
  DCHECK_GE(undoes_, 0);
  DCHECK_GE(executedSize_, 0);

  DCHECK_LE(undoes_, preUndoSize_);
  DCHECK_LE(executedSize_, preUndoSize_);

  editable->onDataChange();
  broadcast(None());
  DLOG(INFO) << "undoable:" << undoable() << ", undoes:" << undoes();
}

bool UndoQueue::write(bool finish) {
  ptr<ActionQueue> events;
  {
    Lock l(lock_);
    int size = queue_.size();
    if (writtenTo_ >= size)
      return false;

    if (!finish && canGroup_(queue_.back()) && writtenTo_ >= --size)
      return false;

    events.reset(new ActionQueue(queue_.begin() + writtenTo_,
                                 queue_.begin() + size));
    writtenTo_ = size;
  }


  for (ActionQueue::iterator i = events->begin(); i != events->end(); ++i)
    logfile_->write(**i);

  logfile_->flush();
  return true;
}

void UndoQueue::start() {
  running_ = true;
}

void UndoQueue::stop() {
  running_ = false;
}

}  // namespace data
}  // namespace rec
