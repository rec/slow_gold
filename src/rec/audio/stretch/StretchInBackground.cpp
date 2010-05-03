#include "juce_amalgamated.h"
#include "rec/audio/stretch/TimeScaler.h"
#include "rec/audio/stretch/StretchInBackground.h"

namespace rec {
namespace audio {
namespace stretch {

using rec::audio::timescaler::Description;

const char* StretchInBackground::THREAD_NAME = "Stretch thread";
const int StretchInBackground::THREAD_PRIORITY = 3;
const int StretchInBackground::INITIAL_SAMPLES = 1024;
const int StretchInBackground::CHUNK_SIZE = 256;

class StretchThread : public Thread {
 public:
  StretchThread(StretchInBackground* base)
      : Thread(StretchInBackground::THREAD_NAME),
        base_(base) {
  }

  virtual void run() {
    const AudioSampleBuffer& source = base_->source_;
    AudioSampleBuffer* target = base_->target_;
    const Description& desc = base_->description_;

    int channels = source.getNumChannels();
    int sourceSize = base_->sourceSize_;
    int sourceOffset = base_->sourcePosition_;
    double scale = desc.timeScale;

    // TODO: I'm a little worried about rounding here but since I don't know
    // what the correct thing to do is here, I might as well round down.
    // This certainly won't work for very small buffers.
    int targetSize = int(sourceSize * scale);
    int targetOffset = int(sourceOffset * scale);

    target->setSize(channels, targetSize);

    float* targetSamples[channels];
    float* sourceSamples[channels];

    AudioTimeScaler scaler;
    desc.Init(&scaler);

    StretchInBackground::Notifier *notifier = base_->notifier_.get();

    for (int written = 0; written < targetSize && !threadShouldExit(); ) {
      int targetChunk = std::min(StretchInBackground::CHUNK_SIZE,
                                 targetSize - targetOffset);
      int64 sourceChunk = scaler.GetInputBufferSize(targetChunk) / 2;

      for (int c = 0; c < channels; ++c) {
        sourceSamples[c] = source.getSampleData(c) + sourceOffset;
        targetSamples[c] = target->getSampleData(c) + targetOffset;
      }
      written += scaler.Process(sourceSamples, targetSamples,
                                sourceChunk, targetChunk);
      if (notifier && written > StretchInBackground::INITIAL_SAMPLES) {
        (*notifier)(targetOffset);
        notifier = NULL;
      }

      sourceOffset = (sourceOffset + sourceSize) % sourceSize;
      targetOffset = (targetOffset + targetSize) % targetSize;
    }
    ScopedLock l(base_->lock_);
    base_->thread_.reset();  // Delete ourselves!
  }

 private:
  StretchInBackground* base_;

  DISALLOW_COPY_AND_ASSIGN(StretchThread);
};


StretchInBackground::StretchInBackground(const Description& description,
                                         const AudioSampleBuffer& source,
                                         int sourceSize,
                                         int sourcePosition,
                                         AudioSampleBuffer* target,
                                         Notifier* notifier = NULL)
  : description_(description),
    source_(source),
    sourceSize_(sourceSize),
    sourcePosition_(sourcePosition),
    target_(target),
    notifier_(notifier) {
}

void StretchInBackground::start() {
  thread_.reset(new StretchThread(this));
  thread_->startThread(StretchInBackground::THREAD_PRIORITY);
}

void StretchInBackground::stop() {
  ScopedLock l(lock_);
  if (thread_)
    thread_->signalThreadShouldExit();
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec
