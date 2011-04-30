#ifndef __REC_EVENT_EVENTQUEUE__
#define __REC_EVENT_EVENTQUEUE__

#include <vector>

#include "rec/base/base.h"

namespace rec { namespace proto { namespace logfile { class Output; }}}

namespace rec {
namespace data {
namespace commands {

class Event;

class EventQueue {
 public:
  explicit EventQueue(const juce::File& file);

  ~EventQueue();

  void add(Event* event);

  void write();

 private:
  typedef std::vector<Event*> EventList;

  EventList events_;
  ptr<proto::logfile::Output> logfile_;
  ptr<juce::CriticalSection> lock_;

  DISALLOW_COPY_AND_ASSIGN(EventQueue);
};

}  // namespace commands
}  // namespace data
}  // namespace rec

#endif  // __REC_EVENT_EVENTQUEUE__
