#include "rec/data/commands/EventQueue.h"
#include "rec/data/proto/LogFile.h"

#include "rec/data/commands/Event.pb.h"


namespace rec {
namespace data {
namespace commands {

EventQueue::EventQueue(const File& file)
    : logfile_(new proto::logfile::Output(file)),
      lock_(new CriticalSection) {
}

EventQueue::~EventQueue() { write(); }

void EventQueue::add(Event* event) {
  ScopedLock l(*lock_);
  events_.push_back(event);
}

void EventQueue::write() {
  EventList events;
  {
    ScopedLock l(*lock_);
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

}  // namespace data
}  // namespace commands
}  // namespace rec
