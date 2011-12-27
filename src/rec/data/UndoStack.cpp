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
      : data_(d), before_(clone(b)), after_(clone(a)), timestamp_(t) {
    if (!timestamp_)
      timestamp_ = juce::Time::currentTimeMillis();
    DCHECK(before_);
    DCHECK(after_);
  }

  static const uint64 MAX_GROUP_TIME = 2000;
  static const bool GROUP_BY_TIME = true;

  // Try to merge another entry into this one;  return true if successful.
  // If this method returns false then neither entry was changed.
  bool mergeInto(UndoStack::Entry* ue) {
    if (ue->data_ != data_ ||
        GROUP_BY_TIME && !near(ue->timestamp_, timestamp_, MAX_GROUP_TIME))
      return false;

    after_.swap(ue->after_);
    return true;
  }

  void setDataValue(bool isBefore) {
    Opener<Message>(data_, CANT_UNDO)->CopyFrom(isBefore ? *before_ : *after_);
  }

  Data* data_;

  ptr<Message> before_;
  ptr<Message> after_;
  int64 timestamp_;
};

UndoStack::~UndoStack() {
  Lock l(lock_);
  stl::deletePointers(&stack_);
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
    ptr<Entry> ue(new Entry(e, before, after));
    if (popRedos() || !stack_.size() || !stack_.back()->mergeInto(ue.get()))
      stack_.push_back(ue.transfer());
  }
  broadcast(None());
}

void UndoStack::redoOrUndo(bool isUndo) {
  int pos = stack_.size() - 1 - (isUndo ? undoes_++ : --undoes_);
  stack_[pos]->setDataValue(isUndo);

  broadcast(None());
}

void UndoStack::undo() {
  if (undoable())
    redoOrUndo(true);
  else
    LOG(DFATAL) << "Tried to undo when nothing was undoable";
}

void UndoStack::redo() {
  if (undoes())
    redoOrUndo(false);
  else
    LOG(DFATAL) << "Tried to redo when nothing was redoable";
}

}  // namespace data
}  // namespace rec
