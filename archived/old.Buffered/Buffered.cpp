#include "rec/audio/source/Buffered.h"

namespace rec {
namespace audio {
namespace source {

BufferDescription BufferDescription::DEFAULT = {2, 2, 4, 4096, 10, 100};

Buffered::Buffered(const String& threadName, const BufferDescription& d)
    : Thread(threadName),
      desc_(d),
      buffers_(d.bufferCount),
      queue_(d.bufferCount),
      wait_(d.wait) {
  setPriority(d.priority);
  for (BufferList::iterator i = buffers_.begin(); i != buffers_.end(); ++i)
    *i = new AudioSampleBuffer(d.channels, d.samples);
}

void Buffered::run() {
  while (!threadShouldExit()) {
    fillBuffers();
    wait(wait_);
  }
}

Buffered::~Buffered() {
  shutdown();
  for (BufferList::iterator i = buffers_.begin(); i != buffers_.end(); ++i)
    delete *i;
}

void Buffered::shutdown() {
  signalThreadShouldExit();
  notify();
  stopThread(desc_.waitForShutdown);
}

void Buffered::init() {
  stopThread(desc_.waitForShutdown);
  offset_ = 0;
  bufferBeingStreamed_ = -1;
  queue_.Clear();
  fillBuffers();
  startThread();
}

void Buffered::fillBuffers() {
  while (true) {
    int buffer;
    {
      ScopedLock l(lock_);
      buffer = queue_.Advance(rec::audio::buffer::EMPTY);
    }

    if (threadShouldExit() || buffer == -1)
      return;

    fillOneBuffer(buffers_[buffer]);
    ScopedLock l(lock_);
    if (threadShouldExit())
      return;

    int full = queue_.Advance(rec::audio::buffer::FILLING);
    if (full != buffer)
      std::cerr << "Filled " << buffer << ", got " << full << std::endl;
    else if (false)
      std::cerr << "Filled buffer " << buffer << " completely." << std::endl;
  }
}

void Buffered::getNextAudioBlock(const AudioSourceChannelInfo& info) {
  int64 toWrite = info.numSamples;
  int64 written = 0;

  while (written < toWrite) {
    if (threadShouldExit())
      return;

    if (bufferBeingStreamed_ == -1) {
      ScopedLock l(lock_);
      bufferBeingStreamed_ = queue_.Advance(rec::audio::buffer::FULL);
      offset_ = 0;
      notify();
    }

    if (bufferBeingStreamed_ == -1) {
      queue_.Output();
      std::cerr << "No full blocks\n";
      break;
    }

    if (threadShouldExit())
      return;

    AudioSampleBuffer* buffer = buffers_[bufferBeingStreamed_];
    int64 bufferSize = buffer->getNumSamples();
    int64 size = std::min(toWrite - written, bufferSize - offset_);

    for (int i = 0; i < info.buffer->getNumChannels(); ++i)
      info.buffer->copyFrom(i, info.startSample + written, *buffer, i, offset_, size);

    if (!offset_)
      notify();

    if (threadShouldExit())
      return;

    written += size;
    offset_ += size;
    if (offset_ >= bufferSize) {
      if (offset_ > bufferSize)
        std::cerr << "wrote too many samples " << offset_ << bufferSize << "\n";

      {
        ScopedLock l(lock_);
        int empty = queue_.Advance(rec::audio::buffer::EMPTYING);
        if (empty != bufferBeingStreamed_) {
          std::cerr << "Expected buffer " << bufferBeingStreamed_
                    << " but got " << empty << std::endl;
          queue_.Output();
        }
        bufferBeingStreamed_ = -1;
      }
      notify();
    }
  }

  if (written < toWrite)
    std::cerr << "Only wrote " << written << " of " << toWrite << " samples.\n";
};

}  // namespace source
}  // namespace audio
}  // namespace rec


