#ifndef __REC_BASE_TRANSLATEDSTRING__
#define __REC_BASE_TRANSLATEDSTRING__

#include <vector>

#include "rec/base/base.h"

namespace rec {

class Trans {
 public:
  operator const String&() const {
    if (!translated_)
      translate();
    return *translated_;
  }

  void translate() const {
    translated_.reset(new String(trans(original_)));
  }

  Trans(const char* o) : original_(o) {}

 private:
  const char* const original_;
  mutable ptr<String> translated_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Trans);
};

}  // namespace rec


#endif  // __REC_BASE_TRANSLATEDSTRING__
