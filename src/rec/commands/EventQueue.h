#ifndef __REC_EVENT_EVENTQUEUE__
#define __REC_EVENT_EVENTQUEUE__

#include <vector>

#include "rec/base/base.h"
#include "rec/base/scoped_ptr.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace proto {
namespace logfile {
class Output;
}  // namespace proto
}  // namespace logfile

namespace commands {

class Event;

class EventQueue {
 public:
  explicit EventQueue(const File& file);

  ~EventQueue();

  void add(Event* event);

  void write();

 private:
  typedef std::vector<Event*> EventList;

  EventList events_;
  scoped_ptr<proto::logfile::Output> logfile_;
  File file_;
  CriticalSection lock_;

  DISALLOW_COPY_AND_ASSIGN(EventQueue);
};

}  // namespace commands
}  // namespace rec

#endif  // __REC_EVENT_EVENTQUEUE__
