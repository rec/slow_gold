#pragma once

#include "rec/base/base.h"

namespace rec {
namespace data {

class Data;

class UndoStack {
  public:
    explicit UndoStack(bool e = false) : undoes_(0), enabled_(e), group_(false) {}
    ~UndoStack();

    void clear();

    void push(Data*, const Message& before, const Message& after);

    int undoable() const { Lock l(lock_); return stack_.size() - undoes_; }
    int undoes() const { Lock l(lock_); return undoes_; }

    void undo();
    void redo();
    void setEnabled(bool e = true);
    void startGroup();
    void stopGroup();
    void updateMenusAndUndo();

  private:
    void undoOrRedo(bool isUndo);
    int popRedos();

    class Entry;
    typedef vector<Entry*> Stack;

    Stack stack_;
    juce::CriticalSection lock_;
    int undoes_;
    bool enabled_;
    bool group_;

    DISALLOW_COPY_ASSIGN_AND_LEAKS(UndoStack);
};

}  // namespace data
}  // namespace rec
