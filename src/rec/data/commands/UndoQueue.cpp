#include "rec/data/commands/UndoQueue.h"
#include "rec/util/file/LogFile.h"

#include "rec/data/commands/Event.pb.h"


namespace rec {
namespace data {
namespace commands {

EventQueue::EventQueue(const File& file)
    : logfile_(new file::Output(file)) {
}

EventQueue::~EventQueue() {
  write();
}

void EventQueue::add(Event* event) {
  ScopedLock l(lock_);
  events_.push_back(event);
}

void EventQueue::write() {
  EventList events;
  {
    ScopedLock l(lock_);
    if (events_.empty())
      return;

    events.swap(events_);
  }

  for (EventList::iterator i = events_.begin(); i != events_.end(); ++i) {
    logfile_->write(**i);
    delete *i;
  }
}

}  // namespace data
}  // namespace commands
}  // namespace rec
