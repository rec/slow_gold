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

  void translate() const;

  Trans(const char* o) : original_(CharPointer_UTF8(o)) {
    check(original_);
  }

  Trans(const String& s) : original_(s) {
    check(original_);
  }

  Trans(const char* o, const char* h)
      : original_(CharPointer_UTF8(o)),
        hint_(CharPointer_UTF8(h)) {
    check(original_);
    check(hint_);
  }

#ifdef DEBUG
  static void dumpAll();
#endif

 private:
  void check(const String& s) {
    DCHECK_GT(s.length(), 0);
    DCHECK(!s.containsChar('\n')) << str(s);
    DCHECK(!s.containsChar('\r')) << str(s);
    DCHECK(!s.containsChar('\t')) << str(s);
    DCHECK(!isspace(s[0])) << str(s);
    DCHECK(!isspace(s[s.length() - 1])) << str(s);
  }

  const String original_;
  const String hint_;

  mutable ptr<String> translated_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Trans);
};

#if JUCE_WINDOWS

inline const wchar_t* c_str(const Trans& s) {
  return c_str(String(s));
}

#else

inline const char* c_str(const Trans& s) {
  return c_str(String(s));
}

#endif

}  // namespace rec


#endif  // __REC_BASE_TRANSLATEDSTRING__
