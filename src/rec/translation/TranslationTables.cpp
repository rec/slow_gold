#include <map>

#include "rec/translation/TranslationTables.h"

#include "rec/base/Trans.pb.h"
#include "rec/data/DataOps.h"
#include "rec/util/Binary.h"
#include "rec/util/Copy.h"
#include "rec/util/STL.h"

namespace rec {
namespace translation {

namespace {

typedef std::map<string, string> StringMap;

string makeHash(const TranslatedString& s) {
  return s.original() + "###" + s.hint();
}

StringMap* makeStringMap(const string& desc) {
  TranslatedStrings ts;
  copy::copy(desc, &ts);
  ptr<StringMap> map(new StringMap);
  for (auto& s: ts.str())
    (*map)[makeHash(s)] = s.translation();

  return map.release();
}

struct Translations {
  Translations() : maps_(app::AppSettings::LAST + 1) {
    maps_[app::AppSettings::NONE] = nullptr;
    maps_[app::AppSettings::DE] =
      makeStringMap(BINARY_STRING(deTranslatedStrings_def));
    maps_[app::AppSettings::EN] =
      makeStringMap(BINARY_STRING(enTranslatedStrings_def));
    maps_[app::AppSettings::ES] =
      makeStringMap(BINARY_STRING(esTranslatedStrings_def));
    maps_[app::AppSettings::FR] =
      makeStringMap(BINARY_STRING(frTranslatedStrings_def));
    maps_[app::AppSettings::ID] =
      makeStringMap(BINARY_STRING(idTranslatedStrings_def));
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
