#ifndef __REC_COMMAND_KEYBOARD__
#define __REC_COMMAND_KEYBOARD__

#include "rec/base/base.h"

namespace rec {
namespace command {

struct Keyboard {
  static juce::XmlElement* create();
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_KEYBOARD__
