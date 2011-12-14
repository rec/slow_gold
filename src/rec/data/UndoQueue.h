#ifndef __REC_EVENT_EVENTQUEUE__
#define __REC_EVENT_EVENTQUEUE__

#include <vector>

#include "rec/data/Action.pb.h"
#include "rec/data/Editable.h"
#include "rec/data/Grouper.h"
#include "rec/util/Listener.h"

namespace rec {
namespace data {

class UndoQueue : public Broadcaster<None> {
 public:
  UndoQueue() : undoes_(0), running_(false) {}
  ~UndoQueue();

  void addToQueue(Editable*, const Message& before, const Message& after);

  int undoable() const { Lock l(lock_); return queue_.size() - undoes_; }
  int undoes() const { Lock l(lock_); return undoes_; }

  void undo();
  void redo();

  void start();
  void stop();

  void dump(const string&) const;

 private:
  void redoOrUndo(bool isUndo);
  bool discardRedos();

  class Entry;
  typedef std::vector<Entry*> Queue;

  Queue queue_;
  juce::CriticalSection lock_;

  int undoes_;

  bool running_;
  DISALLOW_COPY_ASSIGN_AND_LEAKS(UndoQueue);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_EVENT_EVENTQUEUE__
