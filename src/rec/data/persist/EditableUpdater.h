#ifndef __REC_DATA_PERSIST_EDITABLEUPDATER__
#define __REC_DATA_PERSIST_EDITABLEUPDATER__

#include "rec/data/Editable.h"
#include "rec/data/UndoQueue.h"
#include "rec/data/UndoQueue.h"
#include "rec/util/thread/Trash.h"

namespace rec {
namespace data {

class UndoQueue;
class UntypedEditable;

class EditableUpdater {
 private:
  EditableUpdater();
  ~EditableUpdater();

 public:
  // A piece of data got new information!
  void needsUpdate(UntypedEditable*);
  bool update();
  bool write();

  EditableMap* map() { return &map_; }
  CriticalSection* lock() { return &lock_; }
  UndoQueue* undoQueue() { return &undoQueue_; }

  static EditableUpdater* instance() { return instance_; }
  static void start();
  static void stop();

 private:
  static EditableUpdater* instance_;

  CriticalSection lock_;

  EditableSet updateData_;
  EditableSet writeData_;
  EditableMap map_;

  UndoQueue undoQueue_;
  thread_ptr<Thread> updateThread_;
  thread_ptr<Thread> writeThread_;

  DISALLOW_COPY_AND_ASSIGN(EditableUpdater);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_PERSIST_EDITABLEUPDATER__
