#include "rec/audio/stretch/Implementation.h"
#include "rec/util/Math.h"

namespace rec {
namespace audio {
namespace stretch {

static const double EPSILON = 1e-6;

Implementation::Implementation(PositionableAudioSource* source,
                               const StretchParameters& stretch)
        : stretch_(stretch), source_(source), buffer_(2, INITIAL_BUFFER_SIZE) {
    info_.buffer = &buffer_;
    info_.startSample = 0;
}

float** Implementation::getSourceSamples(int numSamples) {
    info_.numSamples = numSamples;
    buffer_.setSize(buffer_.getNumChannels(), numSamples, false, false, true);
    source_->getNextAudioBlock(info_);
    return buffer_.getArrayOfWritePointers();
}

void Implementation::setStretch(const Stretch& s) {
    Lock l(lock_);
    stretch_.mutable_stretch()->CopyFrom(s);
    stretchChanged();
}

void Implementation::setMasterTune(double t) {
    Lock l(lock_);
    if (!near(stretch_.master_tune(), t, EPSILON)) {
        stretch_.set_master_tune(t);
        stretchChanged();
    }
}

void Implementation::setInputSampleRate(SampleRate s) {
    Lock l(lock_);
    if (s != stretch_.input_sample_rate()) {
        stretch_.set_input_sample_rate(s);
        stretchChanged();
    }
}

void Implementation::setOutputSampleRate(SampleRate s) {
    Lock l(lock_);
    if (s != stretch_.output_sample_rate()) {
        stretch_.set_output_sample_rate(s);
        stretchChanged();
    }
}

double Implementation::timeScale() const {
    Lock l(lock_);
    return stretch::timeScale(stretch_);
}

double Implementation::pitchScale() const {
    Lock l(lock_);
    return stretch::pitchScale(stretch_);
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec
