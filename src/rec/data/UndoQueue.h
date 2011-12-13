#ifndef __REC_EVENT_EVENTQUEUE__
#define __REC_EVENT_EVENTQUEUE__

#include <vector>

#include "rec/data/Action.pb.h"
#include "rec/data/Editable.h"
#include "rec/data/Grouper.h"
#include "rec/util/Listener.h"

namespace rec { namespace util { namespace file { class Output; }}}

namespace rec {
namespace data {

class UndoQueue : public Broadcaster<None> {
 public:
  explicit UndoQueue(const juce::File& file,
                     ActionGrouper grouper = NULL,
                     CanGroup can = NULL);

  ~UndoQueue();

  void add(Editable*, const Operations& command, const Operations& undo);

  int undoable() const { Lock l(lock_); return preUndoSize_ - undoes_; }
  int undoes() const { Lock l(lock_); return undoes_; }

  void undo() { if (undoable()) redoOrUndo(Action::UNDO); }
  void redo() { if (undoes_) redoOrUndo(Action::REDO); }

  void start();
  void stop();

  bool write(bool finish = false);

 private:
  void redoOrUndo(Action::Type);

  typedef std::vector<Action*> ActionQueue;

  ActionQueue queue_;
  ptr<file::Output> logfile_;
  juce::CriticalSection lock_;
  EditableList editables_;

  int writtenTo_;
  int undoes_;
  int executedSize_;
  int preUndoSize_;
  bool running_;
  ActionGrouper grouper_;
  CanGroup canGroup_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(UndoQueue);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_EVENT_EVENTQUEUE__
