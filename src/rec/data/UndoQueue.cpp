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

UndoQueue::UndoQueue(const File& file, ActionGrouper grouper)
    : writtenTo_(0),
      undoes_(0),
      executedSize_(0),
      preUndoSize_(0),
      running_(false),
      grouper_(grouper) {
  if (DELETE_UNDO_QUEUE)
    file.deleteFile();
  logfile_.reset(new Output(file));
  if (!grouper_)
    grouper_ = groupCloseActions;
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
  if (!operations.undoable())
    return;
  {
    Lock l(lock_);
    if (!running_)
      return;
  }
  ptr<Action> action(makeAction(Action::OPERATION));
  action->mutable_file()->CopyFrom(e->virtualFile());
  action->set_type_name(e->getTypeName());
  action->set_timestamp(juce::Time::currentTimeMillis());

  action->mutable_operations()->MergeFrom(operations);
  action->mutable_undo()->MergeFrom(undo);

  if (queue_.empty() || !grouper_(queue_.back(), action.get(), e)) {
    queue_.push_back(action.transfer());
    editables_.push_back(e);
    undoes_ = 0;
    preUndoSize_ = executedSize_ = queue_.size();
  }
  broadcast(None());
}

void UndoQueue::undo() {
  if (undoable())
    doOrRedo(Action::UNDO);
}

void UndoQueue::redo() {
  if (undoes_)
    doOrRedo(Action::REDO);
}

void UndoQueue::doOrRedo(Action::Type type) {
  DCHECK(type == Action::UNDO || type == Action::REDO);
  int td = (type == Action::REDO) ? 1 : -1;

  int position = executedSize_ + td;
  if (type == Action::REDO)
    position--;

  if (position < 0 || position >= preUndoSize_) {
    LOG(ERROR) << "CommandIDEncoder is out of range at " << position
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
      LOG(ERROR) << "Tried to " << type << " a " << action->type();
      return;
    }
  }

  Editable* editable = editables_[pos];
  if (!editable) {
    LOG(ERROR) << "No editable for " << type;
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
}

bool UndoQueue::write(bool finish) {
  ptr<ActionQueue> events;
  {
    Lock l(lock_);
    int size = queue_.size();
    if (writtenTo_ >= size)
      return false;

    if (!finish && grouper_(queue_.back(), NULL, NULL)) {
      if (writtenTo_ >= --size)
        return false;
    }

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
