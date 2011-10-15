#ifndef __REC_EVENT_EVENTQUEUE__
#define __REC_EVENT_EVENTQUEUE__

#include <vector>

#include "rec/data/Editable.h"

namespace rec { namespace util { namespace file { class Output; }}}

namespace rec {
namespace data {

class Action;

class UndoQueue {
 public:
  explicit UndoQueue(const juce::File& file);

  ~UndoQueue();

  void add(Editable*, const OperationList& command, const OperationList& undo);
  bool write();

  int undoable() const { Lock l(lock_); return actions_.size() - undoes_; }
  int undoes() const { Lock l(lock_); return undoes_; }

  void undo();
  void redo();

 private:
  void add(Action* event);
  void executeTop(bool isUndo);

  typedef std::vector<Action*> ActionList;

  ActionList actions_;
  ptr<file::Output> logfile_;
  juce::CriticalSection lock_;
  EditableList editables_;

  int writtenTo_;
  int undoes_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(UndoQueue);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_EVENT_EVENTQUEUE__
