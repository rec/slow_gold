#ifndef __REC_BASE_BASE__
#define __REC_BASE_BASE__

#include <string>

#include "rec/base/disallow.h"
#include "rec/base/scoped_ptr.h"
#include "rec/base/types.h"

namespace juce {

class CriticalSection;
class File;
class String;

}

namespace rec {

typedef juce::CriticalSection CriticalSection;
typedef juce::File File;
typedef juce::String String;

typedef std::string string;

}

#endif  // __REC_BASE_BASE__
