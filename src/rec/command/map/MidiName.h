#ifndef __REC_COMMAND_MIDINAME__
#define __REC_COMMAND_MIDINAME__

#include "rec/base/base.h"

namespace rec {
namespace command {

String midiName(const MidiMessage& msg);

struct MidiName {
  static void registerAllTranslations();
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_MIDINAME__
