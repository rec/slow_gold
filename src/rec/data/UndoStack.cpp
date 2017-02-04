#include "rec/data/UndoStack.h"

#include "rec/data/Data.h"
#include "rec/data/Opener.h"
#include "rec/data/Value.h"
#include "rec/data/proto/Equals.h"
#include "rec/program/JuceModel.h"
#include "rec/util/DisableMap.h"
#include "rec/util/Math.h"
#include "rec/util/proto/Proto.h"
#include "rec/util/STL.h"
#include "rec/util/file/LogFile.h"

namespace rec {
namespace data {

class UndoStack::Entry {
  public:
    Entry(Data* d, const Message& undo, const Message& redo, int64 t = 0)
            : data_(d), undo_(clone(undo)), redo_(clone(redo)), timestamp_(t) {
        if (!timestamp_)
            timestamp_ = juce::Time::currentTimeMillis();
        DCHECK(undo_);
        DCHECK(redo_);
        DCHECK_EQ(undo_->GetTypeName(), redo_->GetTypeName());
    }

    static const int64 MAX_GROUP_TIME = 2000;
    static const bool GROUP_BY_TIME = false;

    // Try to merge another entry into this one;  return true if successful.
    // If this method returns false then neither entry was changed.
    bool mergeInto(UndoStack::Entry* ue, bool group) {
        bool merge = mustMerge(*ue, group);
        if (merge)
            redo_.swap(ue->redo_);

        return merge;
    }

    void undoOrRedo(bool isUndo) {
        Opener<Message>(data_, CANT_UNDO)->CopyFrom(isUndo ? *undo_ : *redo_);
    }

    bool mustMerge(const UndoStack::Entry& entry, bool group) {
        if (entry.data_ != data_)
            return false;

        if (GROUP_BY_TIME)
            return near(entry.timestamp_, timestamp_, MAX_GROUP_TIME);

        return group;
    }

    void log() const {
        DLOG(INFO) << "Undo: " << undo_->GetTypeName();
    }

    Data* data_;

    std::unique_ptr<Message> undo_;
    std::unique_ptr<Message> redo_;
    int64 timestamp_;
};

UndoStack::~UndoStack() {
    Lock l(lock_);
    stl::deletePointers(&stack_);
}

void UndoStack::updateMenusAndUndo() {
    program::juceModel()->setProperty("cant_undo", not undoable());
    program::juceModel()->setProperty("cant_redo", not undoes());
}

void UndoStack::clear() {
    {
        Lock l(lock_);
        if (!enabled_)
            return;

        stl::deletePointers(&stack_);
        stack_.clear();
    }
    updateMenusAndUndo();
}

int UndoStack::popRedos() {
    if (!undoes_)
        return 0;

    uint32 newSize = stack_.size() - undoes_;
    for (uint32 i = newSize; i < stack_.size(); ++i)
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

        std::unique_ptr<Entry> ue(new Entry(e, before, after));
        if (popRedos() || !stack_.size() ||
                !stack_.back()->mergeInto(ue.get(), group_)) {
            stack_.push_back(ue.release());
        }
    }
    updateMenusAndUndo();
}

void UndoStack::undoOrRedo(bool isUndo) {
    {
        Lock l(lock_);
        if (!enabled_)
            return;
        int pos = stack_.size() - 1 - (isUndo ? undoes_++ : --undoes_);
        stack_[pos]->undoOrRedo(isUndo);
    }

    updateMenusAndUndo();
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
    updateMenusAndUndo();
}

void UndoStack::startGroup() {
    Lock l(lock_);
    group_ = true;
}

void UndoStack::stopGroup() {
    Lock l(lock_);
    group_ = false;
}

}  // namespace data
}  // namespace rec
