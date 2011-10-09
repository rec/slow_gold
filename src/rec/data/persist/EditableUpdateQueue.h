#ifndef __REC_PERSIST_APPINSTANCE__
#define __REC_PERSIST_APPINSTANCE__

#include <set>
#include "rec/util/thread/Trash.h"

namespace rec {

namespace data { class UntypedEditable; }

namespace persist {

class EditableFactory;

class EditableUpdateQueue {
 public:
  static const int UPDATE_PRIORITY = 5;
  static const int UPDATE_PERIOD = 40;

  static const int WRITE_PRIORITY = 5;
  static const int WRITE_PERIOD = 100;

  // A piece of data got new information!
  virtual void needsUpdate(data::UntypedEditable* data);

  bool update();
  bool write();

  static void start();
  static void stop();

  static EditableUpdateQueue* getInstance() { return instance_; }
  static EditableFactory* getFactory() { return instance_->factory_.get(); }

  typedef std::set<data::UntypedEditable*> DataSet;
  bool running() const;

private:
  virtual ~EditableUpdateQueue();
  explicit EditableUpdateQueue();

  CriticalSection lock_;

  DataSet updateData_;
  DataSet writeData_;

  thread_ptr<Thread> updateThread_;
  thread_ptr<Thread> writeThread_;
  ptr<EditableFactory> factory_;

  static EditableUpdateQueue* instance_;

  DISALLOW_COPY_AND_ASSIGN(EditableUpdateQueue);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_APPINSTANCE__
