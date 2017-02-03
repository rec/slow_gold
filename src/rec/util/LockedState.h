#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {

class LockedState {
  public:
    enum State { WAITING, UPDATING, DELETING };

    LockedState() : state_(WAITING) {}

    State getState() const {
        Lock l(lock_);
        return state_;
    }

    static const int MAX_SPIN_COUNT = 100;

    bool setState(State state) {
        for (int i = 0; i < MAX_SPIN_COUNT; ++i) {
            Lock l(lock_);
            if (state == state_)
                return true;

            if (state_ == DELETING)
                return false;

            if (state_ == WAITING || state == WAITING) {
                state_ = state;
                return true;
            }
            Thread::sleep(1);
        }
        DCHECK(false);
        return false;
    };

  private:
    CriticalSection lock_;
    State state_;

    DISALLOW_COPY_ASSIGN_AND_LEAKS(LockedState);
};

class StateLocker {
  public:
    StateLocker(LockedState* state)
            : state_(state), success_(state_->setState(LockedState::UPDATING)) {
    }

    operator bool() const { return success_; }
    bool operator!() const { return !success_; }

    ~StateLocker() {
        if (success_)
            state_->setState(LockedState::WAITING);
    }

  private:
    LockedState* const state_;
    const bool success_;
};


}  // namespace util
}  // namespace rec
