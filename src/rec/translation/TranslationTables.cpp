#include <map>

#include "rec/translation/TranslationTables.h"

#include "rec/data/DataOps.h"
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

string makeHash(const TranslatedString& s) {
  return s.original() + "###" + s.hint();
}

StringMap* makeStringMap(const TranslatedStrings& ts) {
  ptr<StringMap> map(new StringMap);
  for (int i = 0; i < ts.str_size(); ++i) {
    const TranslatedString& s = ts.str(i);
    (*map)[makeHash(s)] = s.translation();
  }

  return map.release();
}

struct Translations {
  Translations() : maps_(app::AppSettings::LAST + 1) {
    maps_[app::AppSettings::NONE] = nullptr;
    maps_[app::AppSettings::DE] = makeStringMap(*deTranslatedStrings);
    maps_[app::AppSettings::EN] = makeStringMap(*enTranslatedStrings);
    maps_[app::AppSettings::ES] = makeStringMap(*esTranslatedStrings);
    maps_[app::AppSettings::FR] = makeStringMap(*frTranslatedStrings);
    maps_[app::AppSettings::ID] = makeStringMap(*idTranslatedStrings);
  }
  ~Translations() { stl::deletePointers(&maps_); }

  typedef vector<StringMap*> Maps;
  Maps maps_;
};

const Translations& translations() {
  static Translations tr;
  return tr;
}

const CriticalSection& lock() {
  static CriticalSection l;
  return l;
}

}  // namespace

Language getLanguage() {
  Lock l(lock());
  return data::getProto<app::AppSettings>().language();
};

string translate(const TranslatedString& original) {
  Lock l(lock());
  Language lang = getLanguage();
  if (lang == app::AppSettings::EN || lang == app::AppSettings::NONE)
    return original.original();

  if (const StringMap* map = translations().maps_[lang]) {
    StringMap::const_iterator i = map->find(makeHash(original));
    if (i != map->end())
      return i->second;
  }

  LOG(ERROR) << "Couldn't translate " << str(original.original());
  return original.original();
}

}  // namespace translation
}  // namespace rec
