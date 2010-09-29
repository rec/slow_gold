#ifndef __REC_AUDIO_SOURCE_MULTIWRAPPY__
#define __REC_AUDIO_SOURCE_MULTIWRAPPY__

#include <vector>
#include <glog/logging.h>

#include "rec/base/base.h"
#include "rec/audio/source/Source.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace audio {
namespace source {

class MultiWrappy : public Source {
 public:
  typedef std::vector<Source*> SourceVector;

  MultiWrappy() : i_(0) {}

  MultiWrappy(Source* s) : i_(0) {
    source_.push_back(s);
  }

  MultiWrappy(Source* s1, Source* s2) : i_(0) {
    source_.push_back(s1);
    source_.push_back(s2);
  }

  MultiWrappy(Source** s1, Source** s2)
      : source_(s1, s2), i_(0) {
  }

  template <typename Iterator>
  MultiWrappy construct(Iterator begin, Iterator end) {
    MultiWrappy mw;
    mw.source_.insert(0, begin, end);
    return mw;
  }

  ~MultiWrappy() { MWFE(delete *i); }

  int getTotalLength() const      { return source_[i_]->getTotalLength(); }
  int getNextReadPosition() const { return source_[i_]->getNextReadPosition(); }
  bool isLooping() const          { return source_[i_]->isLooping()); }

  void getNextAudioBlock(const AudioSourceChannelInfo& info) {
    source_[i_]->getNextAudioBlock();
    int position = getNextReadPosition();
    for (int i = 0; i < source_.size(); ++i)
      if (i != i_)
        source[i]->setNextReadPosition(position);
    }
  }

// Macros are a BAD idea.  Don't do this.  :-D  Craving C++0x.
#define MWFE(E)                                                     \
  for (SourceVector::iterator i = source_.begin(); i != source.end(); ++i) { \
    E;                                                                  \
  }

  void setNextReadPosition(int p)     { MWFE((*i)->setNextReadPosition(p)); }
  void setLooping(bool looping)       { MWFE((*i)->setLooping(looping)); }
  void prepareToPlay(int s, double r) { MWFE((*i)->prepareToPlay(s, r)); }
  void releaseResources()             { MWFE((*i)->releaseResources()); }

#undef MFWE

#undef _MWFE
#undef MWFE
#undef MWFEC

 protected:
  SourceVector source_;
  int i_;
};


}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_MULTIWRAPPY__
