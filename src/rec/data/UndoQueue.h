#ifndef __REC_EVENT_EVENTQUEUE__
#define __REC_EVENT_EVENTQUEUE__

#include <vector>

#include "rec/data/Editable.h"
#include "rec/data/Action.pb.h"

namespace rec { namespace util { namespace file { class Output; }}}

namespace rec {
namespace data {

class UndoQueue {
 public:
  explicit UndoQueue(const juce::File& file);

  ~UndoQueue();

  void add(Editable*, const Operations& command, const Operations& undo);
  bool write();

  int undoable() const { Lock l(lock_); return queue_.size() - undoes_; }
  int undoes() const { Lock l(lock_); return undoes_; }

  void undo();
  void redo();
  void start();
  void stop();

 private:
  void doOrRedo(Action::Type);

  typedef std::vector<Action*> ActionQueue;

  ActionQueue queue_;
  ptr<file::Output> logfile_;
  juce::CriticalSection lock_;
  EditableList editables_;

  int writtenTo_;
  int undoes_;
  int executedSize_;
  bool running_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(UndoQueue);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_EVENT_EVENTQUEUE__
