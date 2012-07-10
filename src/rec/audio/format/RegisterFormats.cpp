#include "rec/audio/format/RegisterFormats.h"

namespace rec {
namespace audio {
namespace format {

namespace {

using namespace juce;

void registerSoftwareFormats(AudioFormatManager* afm, ReadWrite rw) {
  afm->registerFormat(new WavAudioFormat(), true);
  afm->registerFormat(new AiffAudioFormat(), false);

#if JUCE_USE_MP3AUDIOFORMAT
  if (rw == READ || JUCE_USE_MP3AUDIOFORMAT_WRITE)
    afm->registerFormat(new MP3AudioFormat(), false);
#endif
}

void registerOptionalFormats(AudioFormatManager* afm) {
#if JUCE_USE_FLAC
  afm->registerFormat(new FlacAudioFormat(), false);
#endif

#if JUCE_USE_OGGVORBIS
  afm->registerFormat(new OggVorbisAudioFormat(), false);
#endif
}

}  // namespace

void registerFormats(AudioFormatManager* afm, ReadWrite rw) {
#if (JUCE_MAC || JUCE_IOS)
  if (rw == READ || JUCE_USE_COREAUDIO_WRITE)
    afm->registerFormat(new CoreAudioFormat(), false);
  else
    registerSoftwareFormats(afm, rw);

#elif JUCE_USE_WINDOWS_MEDIA_FORMAT
  registerSoftwareFormats(afm, rw);
  if (rw == READ || JUCE_USE_WINDOWSMEDIA_WRITE)
    afm->registerFormat(new WindowsMediaAudioFormat(), false);
#endif

  registerOptionalFormats(afm);
}

AudioFormatManager* createAudioFormatManager(ReadWrite rw) {
  ScopedPointer<AudioFormatManager> afm(new AudioFormatManager());
  registerFormats(afm, rw);
  return afm.release();
}

}  // namespace format
}  // namespace audio
}  // namespace rec

