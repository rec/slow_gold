#pragma once

#include <typeinfo>
#include <unordered_map>

#include "rec/util/Listener.h"

namespace rec {
namespace util {

class StateBroadcaster {
  public:
    StateBroadcaster() {}

    static StateBroadcaster* instance() {
        static StateBroadcaster INSTANCE;
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
    std::unordered_map<string, std::unique_ptr<Deletable>> broadcasters_;
    CriticalSection lock_;

    DISALLOW_COPY_ASSIGN_AND_LEAKS(StateBroadcaster);
};

template <typename Type>
void broadcastState(Type value) {
    StateBroadcaster::instance()->broadcast<Type>(value);
}

template <typename Type>
class StateListener : public Listener<Type> {
  public:
    explicit StateListener(bool listen = true) {
        if (listen)
            StateBroadcaster::instance()->addListener<Type>(this);
    }

    virtual void operator()(Type) = 0;
};

}  // namespace util
}  // namespace rec
