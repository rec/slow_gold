#include "rec/data/UndoStack.h"

#include "rec/data/Data.h"
#include "rec/data/Opener.h"
#include "rec/data/Value.h"
#include "rec/data/proto/Equals.h"
#include "rec/util/Math.h"
#include "rec/util/STL.h"
#include "rec/util/file/LogFile.h"

namespace rec {
namespace data {

class UndoStack::Entry {
 public:
  Entry(Data* d, const Message& b, const Message& a, int64 t = 0)
      : data_(d), undo_(clone(b)), redo_(clone(a)), timestamp_(t) {
    if (!timestamp_)
      timestamp_ = juce::Time::currentTimeMillis();
    DCHECK(undo_);
    DCHECK(redo_);
  }

  static const uint64 MAX_GROUP_TIME = 2000;
  static const bool GROUP_BY_TIME = true;

  // Try to merge another entry into this one;  return true if successful.
  // If this method returns false then neither entry was changed.
  bool mergeInto(UndoStack::Entry* ue) {
    if (ue->data_ != data_ ||
        GROUP_BY_TIME && !near(ue->timestamp_, timestamp_, MAX_GROUP_TIME))
      return false;

    redo_.swap(ue->redo_);
    return true;
  }

  void undoOrRedo(bool isUndo) {
    Opener<Message>(data_, CANT_UNDO)->CopyFrom(isUndo ? *undo_ : *redo_);
  }

  Data* data_;

  ptr<Message> undo_;
  ptr<Message> redo_;
  int64 timestamp_;
};

UndoStack::~UndoStack() {
  Lock l(lock_);
  stl::deletePointers(&stack_);
}

void UndoStack::clear() {
  {
    Lock l(lock_);
    if (!enabled_)
      return;

    stl::deletePointers(&stack_);
    stack_.clear();
    // DLOG(INFO) << stack_.size() << ", " << undoable() << ", " << undoes();
  }
  broadcast(None());
}

int UndoStack::popRedos() {
  if (!undoes_)
    return 0;

  uint newSize = stack_.size() - undoes_;
  for (uint i = newSize; i < stack_.size(); ++i)
    delete stack_[i];

  stack_.resize(newSize);

  int undoes = undoes_;
  undoes_ = 0;

  return undoes;
}

void UndoStack::push(Data* e, const Message& before, const Message& after) {
  {
    Lock l(lock_);
    if (!enabled_)
      return;

    ptr<Entry> ue(new Entry(e, before, after));
    if (popRedos() || !stack_.size() || !stack_.back()->mergeInto(ue.get()))
      stack_.push_back(ue.transfer());
    // DLOG(INFO) << stack_.size() << ", " << undoable() << ", " << undoes();
  }
  broadcast(None());
}

void UndoStack::undoOrRedo(bool isUndo) {
  {
    Lock l(lock_);
    if (!enabled_)
      return;
    int pos = stack_.size() - 1 - (isUndo ? undoes_++ : --undoes_);
    stack_[pos]->undoOrRedo(isUndo);
    // DLOG(INFO) << stack_.size() << ", " << undoable() << ", " << undoes();
  }

  broadcast(None());
}

void UndoStack::undo() {
  if (undoable())
    undoOrRedo(true);
  else
    LOG(DFATAL) << "Tried to undo when nothing was undoable";
}

void UndoStack::redo() {
  if (undoes())
    undoOrRedo(false);
  else
    LOG(DFATAL) << "Tried to redo when nothing was redoable";
}

void UndoStack::setEnabled(bool e) {
  Lock l(lock_);
  enabled_ = e;
}

}  // namespace data
}  // namespace rec
