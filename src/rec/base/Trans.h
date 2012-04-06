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

  Trans(const char* o) : original_(o) { check(); }
  Trans(const String& o) : original_(o) { check(); }

 private:
  void check() {
    const String& s = original_;
    DCHECK_GT(s.length(), 0);
    DCHECK(!s.containsChar('\n')) << str(s);
    DCHECK(!s.containsChar('\r')) << str(s);
    DCHECK(!s.containsChar('\t')) << str(s);
    DCHECK(!isspace(s[0])) << str(s);
    DCHECK(!isspace(s[s.length() - 1])) << str(s);
  }

  const String original_;
  mutable ptr<String> translated_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Trans);
};

}  // namespace rec


#endif  // __REC_BASE_TRANSLATEDSTRING__
