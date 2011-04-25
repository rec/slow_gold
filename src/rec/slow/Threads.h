#ifndef __REC_SLOW_THREADS__
#define __REC_SLOW_THREADS__

#include "rec/util/thread/Trash.h"

namespace rec {
namespace slow {

class Instance;

class Threads {
 public:
  explicit Threads(Instance* i);
  ~Threads() { stop(); }

  void stop();

  void clock();
  void newFile(const VirtualFile& file);

  const Thread* newFile() const { return newFile_.get(); }

 private:
  Instance* instance_;
  ptr<Thread> clock_;
  ptr<Thread> newFile_;
  Thread* directory_;  // TODO

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Threads);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_THREADS__
