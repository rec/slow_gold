#ifndef __REC_BASE_TRANSLATEDSTRING__
#define __REC_BASE_TRANSLATEDSTRING__

#include <vector>

#include "rec/base/base.h"
#include "rec/base/Internationalization.pb.h"

namespace rec {

class TranslatedString;

typedef Internationalization::Language Language;

class Trans {
 public:
  operator String() const;
  void registerTranslation() const;

  explicit Trans(const char*);  // DEPRECATED
  Trans(const char*, const char* file, int line);
  Trans(const String&, const char* file, int line);
  Trans(const char* o, const char* hint, const char* file, int line);
  ~Trans();

 private:
  ptr<TranslatedString> string_;
  mutable bool translationRegistered_;
  Language language_;
  CriticalSection lock_;

  void check(const string& s);

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Trans);

#ifdef DEBUG
 public:
  static void dumpAll();
#endif
};

#define TRTR(NAME, TEXT)                      \
  const Trans NAME(TEXT, __FILE__, __LINE__)

#define TRTR2(NAME, TEXT, HINT)                \
  const Trans NAME(TEXT, HINT, __FILE__, __LINE__)

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
