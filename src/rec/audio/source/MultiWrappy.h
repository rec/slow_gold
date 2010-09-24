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

// Macros are a BAD idea.  Don't do this.  :-D  Craving C++0x.
#define _MWFE(E, ITER, S)\
 for (ITER i = S.begin(); i != S.end(); ++i) { E; }

#define MWFE(E)\
 _MWFE(E, SourceVector::iterator, source_)

#define MWFEC(E, V)\
 _MWFE(return E, SourceVector::const_iterator, source_);\
 return V;

class MultiWrappy : public Source {
 public:
  typedef std::vector<Source*> SourceVector;

  MultiWrappy() {}

  MultiWrappy(Source* s) {
    source_.push_back(s);
  }

  MultiWrappy(Source* s1, Source* s2) {
    source_.push_back(s1);
    source_.push_back(s2);
  }

  MultiWrappy(Source** s1, Source** s2)
      : source_(s1, s2) {
  }

  template <typename Iterator>
  MultiWrappy construct(Iterator begin, Iterator end) {
    MultiWrappy mw;
    mw.source_.insert(0, begin, end);
    return mw;
  }

  ~MultiWrappy() { MWFE(delete *i); }

  void getNextAudioBlock(const AudioSourceChannelInfo& info) {
    MWFE((*i)->getNextAudioBlock(info));
  }

  int getTotalLength() const          { MWFEC((*i)->getTotalLength(), 0); }
  int getNextReadPosition() const     { MWFEC((*i)->getNextReadPosition(), 0); }
  bool isLooping() const              { MWFEC((*i)->isLooping(), false); }

  void setNextReadPosition(int p)     { MWFE((*i)->setNextReadPosition(p)); }
  void setLooping(bool looping)       { MWFE((*i)->setLooping(looping)); }
  void prepareToPlay(int s, double r) { MWFE((*i)->prepareToPlay(s, r)); }
  void releaseResources()             { MWFE((*i)->releaseResources()); }

#undef _MWFE
#undef MWFE
#undef MWFEC

 protected:
  SourceVector source_;
};


}  // namespace source
}  // namespace audio
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_MULTIWRAPPY__
