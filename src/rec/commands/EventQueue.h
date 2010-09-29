#ifndef __REC_EVENT_EVENTQUEUE__
#define __REC_EVENT_EVENTQUEUE__

#include <vector>

#include "rec/base/basictypes.h"
#include "rec/base/scoped_ptr.h"
#include "rec/event/Event.pb.h"
#include "rec/proto/LogFile.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace event {

class EventQueue {
 public:
  explicit EventQueue(const File& file)
      : file_(file),
        logfile_(new proto::logfile::Output(file)) {
  }

  ~EventQueue() { write(); }

  void add(Event* event) {
    ScopedLock l(lock_);
    events_.push_back(event);
  }

  void write() {
    EventList events;
    {
      ScopedLock l(lock_);
      if (events_.empty())
        return;

      events = events_;
      events_.clear();
    }

    for (EventList::iterator i = events_.begin(); i != events_.end(); ++i) {
      logfile_->write(**i);
      delete *i;
    }
  }

 private:
  typedef std::vector<Event*> EventList;

  EventList events_;
  scoped_ptr<proto::logfile::Output> logfile_;
  File file_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(EventQueue);
};

}  // namespace event
}  // namespace rec

#endif  // __REC_EVENT_EVENTQUEUE__
