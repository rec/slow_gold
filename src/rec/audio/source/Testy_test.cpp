#include <gtest/gtest.h>

#include "rec/audio/source/Testy.h"

namespace rec {
namespace audio {
namespace source {

TEST(RecAudio, Testy) {
    AudioSampleBuffer buffer(2, 128);

    AudioSourceChannelInfo info;
    info.buffer = &buffer;
    info.numSamples = 32;
    info.startSample = 64;

    Testy testy;
    testy.setNextReadPosition(16);
    testy.getNextAudioBlock(info);

    for (int c = 0; c < 2; ++c) {
        for (int i = 0; i < 32; ++i) {
            EXPECT_EQ(Testy::getSample(16 + i),
                      *buffer.getReadPointer(c, 64 + i));
        }
    }
}

}  // namespace source
}  // namespace audio
}  // namespace rec
