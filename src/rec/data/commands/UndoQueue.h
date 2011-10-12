#ifndef __REC_EVENT_EVENTQUEUE__
#define __REC_EVENT_EVENTQUEUE__

#include <vector>

#include "rec/data/Editable.h"

namespace rec { namespace util { namespace file { class Output; }}}

namespace rec {
namespace data {

class UntypedEditable;

namespace commands {

class Action;

class UndoQueue {
 public:
  explicit UndoQueue(const juce::File& file);

  ~UndoQueue();

  void add(Action* event);

  void add(UntypedEditable*, OperationQueue*);
  bool write();

 private:
  typedef std::vector<Action*> ActionList;

  ActionList events_;
  ptr<file::Output> logfile_;
  juce::CriticalSection lock_;
  int writtenTo_;
  int undoneTo_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(UndoQueue);
};

}  // namespace commands
}  // namespace data
}  // namespace rec

#endif  // __REC_EVENT_EVENTQUEUE__
