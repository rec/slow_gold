#ifndef __REC_SLOW_APP_SOURCELISTENER__
#define __REC_SLOW_APP_SOURCELISTENER__

#include "rec/util/listener/Broadcaster.h"

namespace rec {
namespace slow {
namespace app {

class SourceListener : public ChangeListener,
                       public listener::Broadcaster<int> {
 public:
  SourceListener() {}

  virtual void changeListenerCallback(juce::ChangeBroadcaster* obj) {
    broadcast(((PositionableAudioSource*) obj)->getNextReadPosition());
  }

 private:
  DISALLOW_COPY_AND_ASSIGN(SourceListener);
};

class SourceTimeListener : public ChangeListener,
                           public listener::Broadcaster<float> {
 public:
  explicit SourceTimeListener(float sr = 44100f) : sampleRate_(sr) {}

  virtual void changeListenerCallback(juce::ChangeBroadcaster* x) {
    broadcast(((PositionableAudioSource*) x)->getNextReadPosition(sampleRate));
  }

 private:
  const float sampleRate_;
  DISALLOW_COPY_AND_ASSIGN(SourceListener);
};


}  // namespace app
}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_APP_SOURCELISTENER__
