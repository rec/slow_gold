#ifndef __REC_UTIL_JUCE
#define __REC_UTIL_JUCE

// Juce utilities

#include "rec/base/basictypes.h"
#include "JuceLibraryCode/JuceHeader.h"
#include "rec/util/Color.pb.h"

namespace rec {
namespace gui {

inline uint32 makeARGB(const Color& c) {
  if (c.has_argb())
    return c.argb();

  else if (c.has_rgb())
    return (c.alpha() << 24) | c.rgb();

  else
    return (c.alpha() << 24) | (c.red() << 16) | (c.green() << 8) | c.blue();
}

inline Colour makeColor(const Color& color) { return Colour(makeARGB(color)); }
inline void setColor(const Color& c, Graphics* g) { g->setColour(makeColor(c)); }

}  // namespace juce
}  // namespace rec

#endif  // __REC_UTIL_JUCE
