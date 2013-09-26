#ifndef __REC_DATA_DATABROADCASTER__
#define __REC_DATA_DATABROADCASTER__

#include "rec/util/Listener.h"

namespace rec {
namespace data {

class DataBroadcaster {
 public:
  DataBroadcaster() {}

  static DataBroadcaster* instance() {
    static DataBroadcaster INSTANCE;
    return &INSTANCE;
  }

  template <typename Type>
  void addListener(const string& name, Listener<Type>* listener) {
    Broadcaster<Type>* b;
    {
      Lock l(lock_);
      auto& bref = broadcasters_[name];
      b = bref.get();
      if (not b)
        bref.reset(broadcaster = new Broadcaster<Type>);
    }
    b->addListener(listener);
  }

  template <typename Type>
  void broadcast(const string& name, Type value) {
    Broadcaster<Type>* b;
    {
      Lock l(lock_);
      b = dynamic_cast<Broadcaster<Type>*>(broadcasters_.at[name].get());
    }
    b->broadcast(value);
  }

 private:
  std::unordered_map<string, unique_ptr<Deletable>> broadcasters_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataBroadcaster);
};

// TYPE is the full type name, without the rec::.
#define ADD_DATA_LISTENER(TYPE, LISTENER)                         \
  DataBroadcaster::instance()->addListener<TYPE>(#TYPE, listener)

#define BROADCAST_DATA(TYPE, VALUE)                           \
  DataBroadcaster::instance()->broadcast<TYPE>(#TYPE, value)

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATABROADCASTER__
