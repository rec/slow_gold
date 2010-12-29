#ifndef __REC_AUDIO_SOURCE_RUNNY__
#define __REC_AUDIO_SOURCE_RUNNY__

#include "rec/base/base.h"

#include "rec/audio/source/Wrappy.h"
#include "rec/audio/source/Runny.pb.h"
#include "rec/util/Circular.h"

namespace rec {
namespace audio {
namespace source {

class Runny : public Thread, public Wrappy::Position {
 public:
  Runny(Source* source,
  	    const RunnyProto& desc = RunnyProto::default_instance());

  virtual ~Runny();

  virtual void setNextReadPosition(int p);
  virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& info);

  // Try to pre-fill the lookahead buffer.
  // Return true when the buffer is full, false otherwise.
  bool fill();
  virtual void run();

 private:
  AudioSampleBuffer buffer_;
  util::Circular filled_;
  const RunnyProto desc_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Runny);
};

}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_RUNNY__
