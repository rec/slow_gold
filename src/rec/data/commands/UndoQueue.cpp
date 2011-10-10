#include "rec/data/commands/UndoQueue.h"
#include "rec/util/STL.h"
#include "rec/util/file/LogFile.h"

#include "rec/data/commands/Action.pb.h"

namespace rec {
namespace data {
namespace commands {

UndoQueue::UndoQueue(const File& file)
    : logfile_(new file::Output(file)), writtenTo_(0), undoneTo_(0) {
}

UndoQueue::~UndoQueue() {
  write();
  stl::deletePointers(&events_);
}

void UndoQueue::add(Action* event) {
  ScopedLock l(lock_);
  events_.push_back(event);
  ++undoneTo_;
}

void UndoQueue::write() {
  ptr<ActionList> events;
  {
    ScopedLock l(lock_);
    int size = events_.size();
    events.reset(new ActionList(events_.begin() + writtenTo_, events_.end()));
    writtenTo_ = size;
  }

  for (ActionList::iterator i = events->begin(); i != events->end(); ++i)
    logfile_->write(**i);
}

}  // namespace data
}  // namespace commands
}  // namespace rec
