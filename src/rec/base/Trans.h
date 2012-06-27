#ifndef __REC_BASE_TRANSLATEDSTRING__
#define __REC_BASE_TRANSLATEDSTRING__

#include <vector>

#include "rec/base/base.h"

namespace rec {

class Trans {
 public:
  operator const String&() const;
  void translate() const;

  Trans(const char*);
  Trans(const String& s);

  Trans(const char* o, const char* hint);

#ifdef DEBUG
  static void dumpAll();
#endif

 private:
  void check(const String& s);

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
