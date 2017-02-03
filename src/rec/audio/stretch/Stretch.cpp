#include "rec/util/math.h"

#include "rec/audio/stretch/Stretch.h"
#include "rec/audio/util/LimitPitch.h"

namespace rec {
namespace audio {
namespace stretch {

namespace {

const auto MIN_DETUNE_DIFFERENCE = 0.05;

double timeScale(const Stretch& d) {
#ifdef USE_STRETCH_ENABLE
    bool enabled = d.enabled() && d.time_enabled();
#else
    bool enabled = d.time_enabled();
#endif
    return enabled ? (100.0 / d.time_percent()) : 1.0;
}

double pitchScale(const Stretch& d, double detuneCents) {
#ifdef USE_STRETCH_ENABLE
    bool enabled = d.enabled() && d.pitch_enabled();
#else
    bool enabled = d.pitch_enabled();
#endif

    if (!enabled && near(detuneCents, 0.0, MIN_DETUNE_DIFFERENCE))
        return 1.0;

    double cents = detuneCents;
    if (enabled)
        cents += d.detune_cents();

    double semitones = cents / 100.0;
    if (enabled)
        semitones += d.semitone_shift();

    return pow(2.0, limitPitch(semitones) / 12.0);
}

double sampleRateRatio(const StretchParameters& sp) {
    return sp.output_sample_rate() / sp.input_sample_rate();
}

}  // namespace

double timeScale(const StretchParameters& sp) {
    return timeScale(sp.stretch()) * sampleRateRatio(sp);
}

double pitchScale(const StretchParameters& sp) {
    return pitchScale(sp.stretch(), sp.master_tune()) / sampleRateRatio(sp);
}

double pitchSemitones(const StretchParameters& sp) {
    static auto const semitone_log = 12.0 / log(2.0);
    return semitone_log * log(pitchScale(sp));
}

}  // namespace stretch
}  // namespace audio
}  // namespace rec
