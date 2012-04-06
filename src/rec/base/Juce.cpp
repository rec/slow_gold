#include <set>

#include "rec/base/base.h"

#define RECORD_TRANSLATIONS

#ifdef RECORD_TRANSLATIONS

namespace rec {

namespace {

typedef std::set<string> TranslationSet;

TranslationSet* translations() {
  static TranslationSet s;
  return &s;
}

void addTranslation(const String& s) {
  translations()->insert(str(s));
}

}  // namespace

void dumpTranslations() {
  DLOG(INFO) << "Dumping translations " << translations()->size();
  const TranslationSet& t = *translations();
  File file("/tmp/translations.txt");
  file.deleteFile();
  juce::FileOutputStream output(file);
  for (TranslationSet::const_iterator i = t.begin(); i != t.end(); ++i) {
    output.write(i->c_str(), i->size());
    output.writeByte('\n');
  }
}


String trans(const String& s) {
  addTranslation(s);
  return ::juce::translate(s);
}

}  // namespace rec

#endif
