#ifndef __REC_BASE_BASE__
#define __REC_BASE_BASE__

#include <string>

#include "rec/base/disallow.h"
#include "rec/base/scoped_ptr.h"
#include "rec/base/types.h"

namespace rec {

typedef std::string string;

}

namespace juce {

class File;
class CriticalSection;

}

#endif  // __REC_BASE_BASE__
