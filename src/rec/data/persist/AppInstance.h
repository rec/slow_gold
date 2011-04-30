#ifndef __REC_PERSIST_APPINSTANCE__
#define __REC_PERSIST_APPINSTANCE__

#include <set>

#include "rec/data/persist/App.h"
#include "rec/util/thread/Trash.h"

namespace rec {

namespace data { class UntypedData; }

namespace persist {

class AppInstance : public App {
 public:
  static const int UPDATE_PRIORITY = 5;
  static const int UPDATE_PERIOD = 40;

  static const int WRITE_PRIORITY = 5;
  static const int WRITE_PERIOD = 100;

  // A piece of data got new information!
  virtual void needsUpdate(data::UntypedData* data);

  bool update();
  bool write();

  static void start();
  static void stop();

  static AppInstance* getInstance() { return instance_; }

  typedef std::set<data::UntypedData*> DataSet;
  bool running() const;

private:
  virtual ~AppInstance();
  explicit AppInstance();

  CriticalSection lock_;

  DataSet updateData_;
  DataSet writeData_;

  thread_ptr<Thread> updateThread_;
  thread_ptr<Thread> writeThread_;

  static AppInstance* instance_;

  DISALLOW_COPY_AND_ASSIGN(AppInstance);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_APPINSTANCE__
