#ifndef __REC_BASE_TRANSLATEDSTRING__
#define __REC_BASE_TRANSLATEDSTRING__

#include <vector>

#include "rec/base/base.h"

namespace rec {

class TranslatedString {
 public:
  TranslatedString(const char* o, bool translateNow = false) : original_(o) {
    if (translateNow)
      translate();
    else
      STRINGS.push_back(this);
  }

  operator const String&() const {
    return *translated_;
  }

  static void translateAll() {
    for (uint i = 0; i < STRINGS.size(); ++i)
      STRINGS[i]->translate();
  }

 private:
  void translate() {
    translated_.reset(new String(trans(original_)));
  }

  typedef std::vector<TranslatedString*> StringList;

  static StringList STRINGS;

  const char* const original_;
  ptr<String> translated_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TranslatedString);
};

class TrStatic : public TranslatedString {
 public:
  TrStatic(const char* o) : TranslatedString(o, false) {}

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(TrStatic);
};

class TrString : public TranslatedString {
 public:
  TrString(const char* o) : TranslatedString(o, true) {}

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(TrString);
};

}  // namespace rec

#endif  // __REC_BASE_TRANSLATEDSTRING__
