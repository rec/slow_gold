#ifndef __REC_AUDIO_SOURCE_DOUBLERUNNY__
#define __REC_AUDIO_SOURCE_DOUBLERUNNY__

#include "rec/audio/source/Wrappy.h"
#include "rec/audio/source/Runny.h"
#include "rec/util/listener/Broadcaster.h"
#include "rec/util/listener/Listener.h"
#include "rec/util/thread/ChangeLocker.h"
#include "rec/slow/Preferences.h"

namespace rec {
namespace audio {
namespace source {

class DoubleRunny : public Wrappy,
                    public util::listener::Broadcaster<Source*> {
 public:
  DoubleRunny() : Wrappy(NULL) {}
  ~DoubleRunny();

  virtual void getNextAudioBlock(const AudioSourceChannelInfo& info);
  void setPreferences(const slow::proto::Preferences& prefs,
                      int pos = -1, double ratio = 1.0);

 protected:
  virtual Source* source() const;

 private:
  CriticalSection lock_;
  slow::proto::Preferences prefs_;
  scoped_ptr<audio::source::Runny> runny_, nextRunny_;
  double ratio_;

  DISALLOW_COPY_AND_ASSIGN(DoubleRunny);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_DOUBLERUNNY__
