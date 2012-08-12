#ifndef __REC_BASE_BASE__

#include "rec/base/BaseNoJuce.h"  // defines the guards here!

#include "JuceLibraryCode/JuceHeader.h"
#include "rec/base/Juce.h"
#include "rec/base/ptr.h"
#include "rec/base/Trans.h"
#include "rec/base/DropDead.h"

// New features that we don't release are protected with NEW_FEATURES.
#ifdef DEBUG
#define NEW_FEATURES
#endif

namespace rec {

inline void doLog(const String& s) {
  File f = File::getSpecialLocation(File::userDesktopDirectory).
    getChildFile("SlowGold.log");
  f.appendText(s);
};

}  // namespace

#endif
