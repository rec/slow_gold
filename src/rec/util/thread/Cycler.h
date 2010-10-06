#ifndef __REC_THREAD_CYCLER__
#define __REC_THREAD_CYCLER__

#include "rec/util/thread/Runnable.h"

namespace rec {
namespace thread {

class Cycler : public Runnable {
 public:
  Cycler() : index_(0) {}

  explicit Cycler(Runnable* r) : index_(0) {
    cycle_.push_back(r);
  }

  Cycler(Runnable* r1, Runnable* r2) : index_(0) {
    cycle_.push_back(r1);
    cycle_.push_back(r2);
  }

  virtual void run(Thread* thread) {
    if (!cycle_.empty())
      cycle_[index_]->run(thread);

    if (++index_ >= cycle_.size())
      index_ = 0;
  }

  virtual ~Cycler() {
    for (Cycle::iterator i = cycle_.begin(); i != cycle_.end(); ++i)
      delete *i;
  }

 protected:
  typedef std::vector<Runnable*> Cycle;
  Cycle cycle_;
  int index_;

 private:
  DISALLOW_COPY_AND_ASSIGN(Cycler);
};

}  // namespace thread
}  // namespace rec

#endif  // __REC_THREAD_CYCLER__
