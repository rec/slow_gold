#pragma once

#include "rec/audio/source/Wrappy.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/StateListener.h"

namespace rec {
namespace audio {
namespace source {

class Timer : public Wrappy, public StateListener<Thread*> {
  public:
    explicit Timer(PositionableAudioSource* s) : Wrappy(s), thread_(nullptr) {}

    virtual void getNextAudioBlock(const AudioSourceChannelInfo& i) {
        Wrappy::getNextAudioBlock(i);
        if (isRunning())
            thread_->notify();
    }

    virtual void setNextReadPosition(int64 time) {
        DCHECK_GE(time, 0);
        Wrappy::setNextReadPosition(time);
        if (isRunning())
            thread_->notify();
    }

    void operator()(Thread* t) override { thread_ = t; }

    void broadcastTime() {
            //if (isRunning())
        broadcastState<SampleTime>(getNextReadPosition());
    }

  private:
    Thread* thread_;

    bool isRunning() const {
        return thread_ and not thread_->threadShouldExit();
    }


    DISALLOW_COPY_ASSIGN_AND_LEAKS(Timer);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

