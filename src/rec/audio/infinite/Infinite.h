#pragma once

#include "rec/base/base.h"

namespace rec {
namespace audio {
namespace infinite {


// A SampleBlock is a sequence of Samples in memory.
// A "skip_" value lets a SampleBlock represent either parallel or
// interleaved samples.
//
// A SampleBlock identifies the samples in
//
//   samples_[0]
//   samples_[skip_]
//   samples_[2 * skip_]
//   ...
//   samples_[(length_ - 1) * skip]
//
// So samples_ must have at least (1 + (length_ - 1) * skip) Samples.

template <typename Sample>
struct SampleBlock {
  vector<Sample*> samples_;  // Vector of sample pointers, one per channel.
  int length_;                    // Number of samples in this block.
  int skip_;                      // Number of samples to skip between frames.

  int channels() const { return samples_.size(); }
};

template <typename Sample> long long getSampleCount();

template <> long long getSampleCount<short>() { return 0x10000; }
template <> long long getSampleCount<int>() { return 0x100000000LL; }


// This is the abstract base class for an infinite player that will eventually
// play every possible sound.
//
// An implementation of Infinite should satisfy the following contract.
//
// The number of possible sample blocks for Sample, channels_, length_ is
//   possibleBlocks = getSampleCount<Sample>() ** (channels_ * length_);
//
// In the following code sample:
//
//    void run(const Infinite& inf, SampleBlock<Sample>* block) {
//      initialize(block);
//      while (increment(block));
//    }
// the while loop must execute exactly possibleBlocks times, and the
// contents of SampleBlock must cycle through all possible possibleBlocks
// states - though the order may be determined by the Infinite and calling
// initialize twice might result in different states of SampleBlock.
//
// An implementation of Infinite should also not contain any mutable internal
// state if at all possible.
//

template <typename Sample>
class Infinite {
 public:
  Infinite() {}

  // The number of channels of output.  This won't change over the life of the
  // Infinite, and all SampleBlocks will have this many channels.
  virtual int channels() const = 0;

  // initialize() fills the SampleBlock regardless of its current contents.
  virtual void initialize(SampleBlock* blocks) const = 0;

  // increment() takes the current SampleBlock contents and changes them to the
  // next SampleBlock state in sequence and returns true IF such a state exists,
  // otherwise increment() returns false;
  virtual bool increment(SampleBlock* blocks) const = 0;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(Infinite);
};

}  // namespace infinite
}  // namespace audio
}  // namespace rec

