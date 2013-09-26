#ifndef __REC_DATA_DATABROADCASTER__
#define __REC_DATA_DATABROADCASTER__

#include <typeinfo>
#include <unordered_map>

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
  void addListener(Listener<Type>* listener) {
    Broadcaster<Type>* b;
    auto name = typeid(Type).name();
    {
      Lock l(lock_);
      auto& bref = broadcasters_[name];
      b = dynamic_cast<Broadcaster<Type>*>(bref.get());
      if (not b)
        bref.reset(b = new Broadcaster<Type>);
    }
    b->addListener(listener);
  }

  template <typename Type>
  void broadcast(Type value) {
    Broadcaster<Type>* b;
    auto name = typeid(Type).name();
    {
      Lock l(lock_);
      auto& bref = broadcasters_.at(name);
      b = dynamic_cast<Broadcaster<Type>*>(bref.get());
    }
    if (b)
      b->broadcast(value);
    else
      LOG(DFATAL) << "Couldn't broadcast to " << name;
  }

  void clear() {
    broadcasters_.clear();
  }

 private:
  std::unordered_map<string, unique_ptr<Deletable>> broadcasters_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataBroadcaster);
};

template <typename Type>
void addDataListener(Listener<Type>* listener) {
  DataBroadcaster::instance()->addListener<Type>(listener);
}

template <typename Type>
void broadcastData(Type value) {
  DataBroadcaster::instance()->broadcast<Type>(value);
}

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATABROADCASTER__
