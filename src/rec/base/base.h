#ifndef __REC_BASE_BASE__

#include <stdlib.h>
#include <stdio.h>

#include "rec/base/BaseNoJuce.h"  // defines the guards here!

#include "JuceLibraryCode/JuceHeader.h"
#include "rec/base/Juce.h"
#include "rec/base/ptr.h"
#include "rec/base/Trans.h"

// New features that we don't release are protected with NEW_FEATURES.
#ifdef DEBUG
#define NEW_FEATURES
#endif

namespace rec {

inline void doLog(const String& s) {
// For very hard to debug problems.
#ifdef NEVER
  File f = File::getSpecialLocation(File::userDesktopDirectory).
    getChildFile("SlowGold.log");
  f.appendText(s);
  f.appendText("\n");
#endif
};

}  // namespace

#endif
