#include "rec/audio/source/Selection.h"
#include "rec/audio/util/Clear.h"
#include "rec/util/range/WrapSeries.h"
#include "rec/util/range/MakeRange.h"

namespace rec {
namespace audio {
namespace source {

void Selection::getNextAudioBlock(const juce::AudioSourceChannelInfo& ai) {
    SampleRangeVector sel = selection();
    SampleTime pos = getNextReadPosition();
    if (sel.empty() or not sel.begin()->end_) {
        clear(ai);
        return;
    }
    AudioSourceChannelInfo info = ai;
    SampleRangeVector blocks = getUnfilledBlocks(sel, pos,
                                                                                              SampleTime(info.numSamples),
                                                                                              WRAP);

    for (SampleRangeVector::const_iterator i = blocks.begin(); i != blocks.end();
              ++i) {
        setNextReadPosition(i->begin_);
        info.numSamples = static_cast<int>(i->size());
        Wrappy::getNextAudioBlock(info);
        info.startSample += info.numSamples;
    }
}

int64 Selection::getTotalLength() const {
    Lock l(lock_);
#ifdef CORRECT_SIZE_CALCULATIONS
    return getCorrectTotalLength();
#else
    return Wrappy::getTotalLength();
#endif
}

int64 Selection::getCorrectTotalLength() const {
    Lock l(lock_);
    return makeRange<SampleTime>(selection_).size();
}

}  // namespace source
}  // namespace audio
}  // namespace rec
