#include <set>

#include "rec/base/base.h"

namespace rec {

#define RECORD_TRANSLATIONS

#ifdef RECORD_TRANSLATIONS
namespace {

typedef std::set<string> TranslationSet;

TranslationSet* translations() {
  static TranslationSet s;
  return &s;
}

void addTranslation(const String& s) {
  translations()->insert(str(s.replace ("\n", "\\n")));
}

}  // namespace

void dumpTranslations() {
  const TranslationSet& t = *translations();
  juce::FileOutputStream output(File("/tmp/translations.txt"));
  for (TranslationSet::const_iterator i = t.begin(); i != t.end(); ++i) {
    output.write(i->c_str(), i->size());
    output.writeByte('\n');
  }
}

#else

void dumpTranslations() {
}

#endif

String translate(const String& s) {
#ifdef RECORD_TRANSLATIONS
  addTranslation(s);
#endif

  return ::juce::translate(s);
}

}  // namespace rec
