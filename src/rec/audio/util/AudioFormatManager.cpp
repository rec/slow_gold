#include "rec/audio/util/AudioFormatManager.h"
#include "rec/audio/format/mpg123/Format.h"

namespace rec {
namespace audio {

static AudioFormatManager* getInstance() {
  ptr<AudioFormatManager> afm(new AudioFormatManager());
  afm->registerBasicFormats();
  afm->registerFormat(new format::mpg123::Format(), false);

  return afm.transfer();
}

AudioFormatManager* getAudioFormatManager() {
  static ptr<AudioFormatManager> instance(getInstance());
  return instance.get();
}

}  // namespace audio
}  // namespace rec
