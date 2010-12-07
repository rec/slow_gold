#ifndef __REC_AUDIO_SOURCE_DOUBLERUNNY__
#define __REC_AUDIO_SOURCE_DOUBLERUNNY__

#include "rec/audio/source/Source.h"
#include "rec/util/listener/Listener.h"
#include "rec/slow/Preferences.h"

namespace rec {
namespace audio {
namespace source {

typedef util::listener::Listener<const slow::proto::Preferences&>
  PreferencesListener;

class DoubleRunny : public Wrappy, public PreferencesListener {
 public:
  DoubleRunny() : Wrappy(NULL) {}
  ~DoubleRunny();

  virtual void operator()(const slow::proto::Preferences& prefs);
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info);

 protected:
  virtual Source* source();

 private:
  CriticalSection lock_;
  Preferences prefs_;
  scoped_ptr<Runny> runny_, nextRunny_;
  double ratio_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(DoubleRunny);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLERUNNY__
