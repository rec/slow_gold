#include <map>

#include "rec/translation/TranslationTables.h"

#include "rec/translation/de-TranslatedStrings.def.h"
#include "rec/translation/en-TranslatedStrings.def.h"
#include "rec/translation/es-TranslatedStrings.def.h"
#include "rec/translation/fr-TranslatedStrings.def.h"
#include "rec/translation/id-TranslatedStrings.def.h"
#include "rec/util/STL.h"

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
  Translations() : maps_(Internat::LAST + 1) {
    maps_[Internat::DE] = makeStringMap(*deTranslatedStrings);
    maps_[Internat::EN] = makeStringMap(*enTranslatedStrings);
    maps_[Internat::ES] = makeStringMap(*esTranslatedStrings);
    maps_[Internat::FR] = makeStringMap(*frTranslatedStrings);
    maps_[Internat::ID] = makeStringMap(*idTranslatedStrings);
  }
  ~Translations() { stl::deletePointers(&maps_); }

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

Language LANGUAGE = Internat::EN;

}  // namespace


void setLanguage(Language lang) {
  Lock l(lock());
  LANGUAGE = lang;
};

Language getLanguage() {
  Lock l(lock());
  return LANGUAGE;
};


string translate(const TranslatedString& translation) {
  return string();
}

}  // namespace translation
}  // namespace rec
