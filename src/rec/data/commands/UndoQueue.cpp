#include "rec/data/commands/UndoQueue.h"
#include "rec/util/file/LogFile.h"

#include "rec/data/commands/Action.pb.h"

namespace rec {
namespace data {
namespace commands {

UndoQueue::UndoQueue(const File& file)
    : logfile_(new file::Output(file)) {
}

UndoQueue::~UndoQueue() {
  write();
}

void UndoQueue::add(Action* event) {
  ScopedLock l(lock_);
  events_.push_back(event);
}

void UndoQueue::write() {
  ActionList events;
  {
    ScopedLock l(lock_);
    if (events_.empty())
      return;

    events.swap(events_);
  }

  for (ActionList::iterator i = events_.begin(); i != events_.end(); ++i) {
    logfile_->write(**i);
    delete *i;
  }
}

}  // namespace data
}  // namespace commands
}  // namespace rec
