#ifndef __REC_DATA_PERSIST_EDITABLEUPDATER__
#define __REC_DATA_PERSIST_EDITABLEUPDATER__

#include "rec/data/Editable.h"
#include "rec/data/UndoQueue.h"
#include "rec/util/thread/Trash.h"

namespace rec {

namespace util { class DefaultRegistry; }

namespace data {

class DataRegistry;
class UndoQueue;
class UntypedEditable;

class EditableUpdater {
 private:
  explicit EditableUpdater(DefaultRegistry*);
  ~EditableUpdater();

 public:
  // A piece of data got new information!
  void needsUpdate(UntypedEditable*);
  bool update();
  bool write();

  EditableMap* map() { return &map_; }
  UndoQueue* undoQueue() { return &undoQueue_; }
  void registerMessage(const Message&);

  const DefaultRegistry& defaultRegistry() { return *defaultRegistry_; }

  static EditableUpdater* instance() { return instance_; }
  static void start(DefaultRegistry*);
  static void stop();
  CriticalSection* lock() { return &lock_; }

 private:
  static EditableUpdater* instance_;

  CriticalSection lock_;

  EditableMap map_;
  UndoQueue undoQueue_;
  ptr<DefaultRegistry> defaultRegistry_;
  ptr<data::DataRegistry> dataRegistry_;

  EditableSet updateData_;
  EditableSet writeData_;
  thread_ptr<Thread> updateThread_;
  thread_ptr<Thread> writeThread_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(EditableUpdater);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PERSIST_EDITABLEUPDATER__
