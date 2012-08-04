#include <map>

#include "rec/translation/TranslationTables.h"

#include "rec/translation/de-TranslatedStrings.def.h"
#include "rec/translation/es-TranslatedStrings.def.h"
#include "rec/translation/fr-TranslatedStrings.def.h"
#include "rec/translation/id-TranslatedStrings.def.h"

namespace rec {
namespace translation {

namespace {

typedef std::map<string, string> StringMap;

string makeHash(const TranslatedString s) {
  return s.original() + "###" + s.hint();
}

StringMap* makeStringMap(const TranslatedStrings& ts) {
  ptr<StringMap> map(new StringMap);
  for (int i = 0; i < ts.str_size(); ++i) {
    const TranslatedString& s = ts.str(i);
    (*map)[makeHash(s)] = s.translation();
  }

  return map.transfer();
}

struct Translations {
  Translations() : maps_(rec::Language::LAST + 1, NULL) {
    maps_[Language::DE] = makeStringMap(*deTranslatedStrings);
    maps_[Language::EN] = makeStringMap(*enTranslatedStrings);
    maps_[Language::ES] = makeStringMap(*esTranslatedStrings);
    maps_[Language::FR] = makeStringMap(*frTranslatedStrings);
    maps_[Language::ID] = makeStringMap(*idTranslatedStrings);
  }
  ~Translations() { stl::deletePointers(&map_); }

  typedef std::vector<StringMap*> Maps;
  Maps maps_;
};

const Translations& translation() {
  static Translations tr;
  return tr;
}

const CriticalSection& lock() {
  static CriticalSection l;
  return l;
}

Language LANGUAGE = Language::ENGLISH;

}  // namespace


void setLanguage(Language lang) {
  ScopedLock l(lock());
  LANGUAGE = lang;
};

Language getLanguage() {
  ScopedLock l(lock());
  return LANGUAGE;
};


string translate(const TranslatedString& translation) {
  return string();
}

}  // namespace translation
}  // namespace rec
