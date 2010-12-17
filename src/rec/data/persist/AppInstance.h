#ifndef __REC_PERSIST_APPINSTANCE__
#define __REC_PERSIST_APPINSTANCE__

#include <set>

#include "rec/data/persist/App.h"
#include "rec/util/thread/RunnableThread.h"


namespace rec {
namespace persist {

class UntypedData;

class AppInstance : public App {
 public:
  static const int UPDATE_PRIORITY = 5;
  static const int UPDATE_PERIOD = 40;

  static const int WRITE_PRIORITY = 5;
  static const int WRITE_PERIOD = 100;

  // A piece of data got new information!
  virtual void needsUpdate(UntypedData* data);

  bool update();
  bool write();

  static void start(const string& name);
  static void stop();

  static AppInstance* getInstance() { return instance_; }

  typedef std::set<UntypedData*> DataSet;

private:
  virtual ~AppInstance();
  explicit AppInstance(const string& appName);

  CriticalSection lock_;

  DataSet updateData_;
  DataSet writeData_;

  thread::RunnableThread updateThread_;
  thread::RunnableThread writeThread_;

  static AppInstance* instance_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(AppInstance);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_APPINSTANCE__
