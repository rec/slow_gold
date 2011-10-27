#ifndef __REC_DATA_PERSIST_EDITABLEUPDATER__
#define __REC_DATA_PERSIST_EDITABLEUPDATER__

#include "rec/data/Editable.h"
#include "rec/data/UndoQueue.h"
#include "rec/util/thread/Trash.h"

namespace rec {
namespace data {

class DefaultRegistry;
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
  CriticalSection* lock() { return &lock_; }
  UndoQueue* undoQueue() { return &undoQueue_; }
  const DefaultRegistry& defaultRegistry() { return *defaultRegistry_; }

  static EditableUpdater* instance() { return instance_; }
  static void start(DefaultRegistry*);
  static void stop();

 private:
  static EditableUpdater* instance_;

  CriticalSection lock_;

  EditableMap map_;
  UndoQueue undoQueue_;
  ptr<DefaultRegistry> defaultRegistry_;

  EditableSet updateData_;
  EditableSet writeData_;
  thread_ptr<Thread> updateThread_;
  thread_ptr<Thread> writeThread_;

  DISALLOW_COPY_AND_ASSIGN(EditableUpdater);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PERSIST_EDITABLEUPDATER__
