#ifndef __REC_EVENT_EVENTSTACK__
#define __REC_EVENT_EVENTSTACK__

#include <vector>

#include "rec/util/Listener.h"

namespace rec {
namespace data {

class Data;

class UndoStack : public Broadcaster<None> {
 public:
  explicit UndoStack(bool enabled = false) : undoes_(0), enabled_(enabled) {}
  ~UndoStack();

  void clear();

  void push(Data*, const Message& before, const Message& after);

  int undoable() const { Lock l(lock_); return stack_.size() - undoes_; }
  int undoes() const { Lock l(lock_); return undoes_; }

  void undo();
  void redo();
  void setEnabled(bool e = true);

 private:
  void undoOrRedo(bool isUndo);
  int popRedos();

  class Entry;
  typedef std::vector<Entry*> Stack;

  Stack stack_;
  juce::CriticalSection lock_;
  int undoes_;
  bool enabled_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(UndoStack);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_EVENT_EVENTSTACK__
