#ifndef __REC_PERSIST_APP__
#define __REC_PERSIST_APP__

#include <set>
#include <string>
#include <glog/logging.h>

#include "rec/persist/AppBase.h"
#include "rec/persist/Data.h"
#include "rec/util/STL.h"
#include "rec/thread/RunnableThread.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace persist {

class UntypedData;

class App : public AppBase {
 public:
  static const int UPDATE_PRIORITY = 5;
  static const int UPDATE_PERIOD = 100;

  static const int WRITE_PRIORITY = 5;
  static const int WRITE_PERIOD = 100;

  // A piece of data got new information!
  virtual void needsUpdate(UntypedData* data);

  void update();
  void write();

  static void start(const string& name);
  static void stop();
  static File appDir(const string& name);

  static App* getInstance() { return instance_; }

  typedef std::set<UntypedData*> DataSet;

private:
  explicit App(const string& appName);
  virtual ~App();

  const File appDir_;
  CriticalSection lock_;

  DataSet updateData_;
  DataSet writeData_;

  thread::RunnableThread updateThread_;
  thread::RunnableThread writeThread_;

  static App* instance_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(App);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_APP__
