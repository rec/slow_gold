#include "rec/data/UndoQueue.h"
#include "rec/data/Action.pb.h"
#include "rec/data/Editable.h"
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
      running_(false),
      grouper_(grouper),
      canGroup_(false) {
  if (DELETE_UNDO_QUEUE)
    file.deleteFile();
  logfile_.reset(new Output(file));
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
    if (!running_)
      return;
  }
  ptr<Action> action(makeAction(Action::OPERATION));
  action->mutable_file()->CopyFrom(e->virtualFile());
  action->set_type_name(e->getTypeName());
  action->set_timestamp(juce::Time::currentTimeMillis());

  action->mutable_operations()->MergeFrom(operations);
  action->mutable_undo()->MergeFrom(undo);

  if (!canGroup_ || queue_.empty() || !grouper_(queue_.back(), action.get(), e)) {
    canGroup_ = grouper_(action.get(), NULL, e);
    queue_.push_back(action.transfer());
    editables_.push_back(e);
    undoes_ = 0;
    executedSize_ = queue_.size();
  }
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
  undoes_ -= td;
  executedSize_ += td;
  canGroup_ = false;

  int position = executedSize_;
  if (type == Action::REDO) {
    position++;
  }

  if (position < 0 || position >= queue_.size()) {
    LOG(ERROR) << "Position is out of range at " << position;
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
  if (t == Action::UNDO)
    editable->applyOperations(action->undo(), action->mutable_operations());
  else
    editable->applyOperations(action->operations());

  ptr<Action> newAction(makeAction(type));
  newAction->set_undo_index(position);
  queue_.push_back(newAction.transfer());
  editables_.push_back(NULL);
  executedSize_ = queue_.size();
}

bool UndoQueue::write(bool finish) {
  ptr<ActionQueue> events;
  {
    Lock l(lock_);
    int size = queue_.size() + (canGroup_ ? -1 : 0);
    if (writtenTo_ >= size)
      return false;

    events.reset(new ActionQueue(queue_.begin() + writtenTo_,
                                 queue_.begin() + size));
  }

  static const bool CLEAR_OPERATIONS = false;

  for (ActionQueue::iterator i = events->begin(); i != events->end(); ++i) {
    Action action(**i);
    if (CLEAR_OPERATIONS)
      action.mutable_operations()->Clear();  // These are redundant.
    logfile_->write(action);
  }
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
