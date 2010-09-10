#ifndef __REC_UTIL_RUNNABLE
#define __REC_UTIL_RUNNABLE

#include "rec/base/basictypes.h"
#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace runnable {

class Runnable {
 public:
  virtual ~Runnable() {}
  virtual void run(Thread* thread) = 0;
  void operator(Thread* thread)() { run(thread); }
};

class Wrapper : public Runnable {
 public:
  Wrapper(Runnable* r) : runnable_(r) {}
  virtual void run(Thread* thread) { runnable_->run(thread); }

 protected:
  Runnable* runnable_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Wrapper);
};

class RunnableThread : public Thread, public Wrapper {
 public:
  RunnableThread(const String& n, Runnable* r) : Thread(n), Wrapper(r) {}
  virtual void run() { runnable_->run(this); }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Thread);
};

class Loop : public Wrapper {
 public:
  Loop(Runnable* r) : Wrapper(r) {}

  virtual void run(Thread* thread) {
    while (!thread->threadShouldExit())
      runnable_->run();
  }

 protected:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Loop);
};

class Waiter : public Runnable {
 public:
  Waiter(int time) : time_(time) {}
  virtual void run(Thread* thread) {
    if (!thread->threadShouldExit())
      thread->wait(time_);
  }

 private:
  const int time_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Waiter);
};

class Waiter : public Runnable {
 public:
  Waiter(int time) : Wrapper(r), time_(time) {}
  virtual void run(Thread* thread) {
    if (!thread->threadShouldExit())
      thread->wait(time_);
  }

 private:
  const int time_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Waiter);
};

1class Cycler : public Runnable {
 public:
  Cycler() {}
  Cycler(Runnable* r) {
    cycle_.push_back(r);
  }
  Cycler(Runnable* r1, Runnable* r2) {
    cycle_.push_back(r1);
    cycle_.push_back(r2);
  }

 protected:
  typedef std::vector<Runnable*> Cycle;
  Cycle cycle_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Cycler);
};


using rec::gui::ThreadDescription ThreadDescription;



class eWrapper : public Runnable {
 public:
  RunnableWrapper(Runnable* r) : runnable_(r) {}
  virtual void run() { runnable->run(); }



}  // namespace runnable
}  // namespace rec

#endif  // __REC_UTIL_RUNNABLE
