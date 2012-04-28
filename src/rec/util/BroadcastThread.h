#ifndef __REC_UTIL_BROADCASTTHREAD__
#define __REC_UTIL_BROADCASTTHREAD__

#include <list>

#include "rec/util/HasLock.h"

namespace rec {
namespace util {

class Callable {
 public:
  explicit Callable(void* owner = NULL) : owner_(owner) {}
  virtual ~Callable() {}
  virtual void call() {}

  bool operator()(Callable* c) const { return c->owner_ == owner_; }

 private:
  void* const owner_;
};

class BroadcastThread : public Thread, public HasLock {
 public:
  BroadcastThread() : Thread("Broadcast thread") {}
  ~BroadcastThread();

  virtual void run();

  void add(Callable* c);
  void remove(void* owner);
  static BroadcastThread* instance();

 private:
  typedef std::list<Callable*> CallableList;
  CallableList callables_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(BroadcastThread);
};

template <typename Broadcaster, typename Type>
struct BroadcasterCallable : public Callable {
  BroadcasterCallable(Broadcaster* broadcaster, Type v)
      : Callable(broadcaster), broadcaster_(broadcaster), value_(v) {
  }
  virtual void call() { broadcaster_->broadcast(value_); }

  Broadcaster* broadcaster_;
  Type value_;
};

template <typename Broadcaster, typename Type>
void broadcastAsync(Broadcaster* b, Type v) {
  BroadcastThread::instance()->add(
      new BroadcasterCallable<Broadcaster, Type>(b, v));
}

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_BROADCASTTHREAD__
