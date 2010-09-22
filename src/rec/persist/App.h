#ifndef __REC_PERSIST_APP__
#define __REC_PERSIST_APP__

#include <map>
#include <string>
#include <glog/logging.h>

#include "rec/persist/Data.h"
#include "rec/persist/Writeable.h"
#include "rec/util/STL.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace persist {

class UntypedData;

class App : public AppBase {
 public:
  static const int UPDATE_PRIORITY = 5;
  static const int UPDATE_THREAD_PERIOD = 100;

  static const int WRITE_PRIORITY = 5;
  static const int WRITE_PERIOD = 100;

  // A piece of data got new information!
  virtual void needsUpdate(UntypedData* data);

  void update();
  void write();

  static void start(const String& name);
  static void stop();
  static File appDir(const String& name);

 private:
  explicit App(const String& appName);
  virtual ~App() {}

  const File appDir_;
  CriticalSection lock_;
  DataRegistry registry_;

  DataList updateData_;
  DataList writeData_;

  RunnableThread updateThread_;
  RunnableThread writeThread_;

  static App* instance_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(App);
};

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_APP__
