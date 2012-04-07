#include <set>

#include "rec/base/base.h"

#ifdef DEBUG

namespace rec {

namespace {

typedef std::pair<string, string> StringPair;
typedef std::set<StringPair> TranslationSet;

TranslationSet* translations() {
  static TranslationSet s;
  return &s;
}

void addTranslation(const String& s, const String& hint) {
  translations()->insert(std::make_pair(str(s), str(hint)));
}

}  // namespace

void Trans::dumpAll() {
  DLOG(INFO) << "Dumping translations " << translations()->size();

  const TranslationSet& t = *translations();
  File file("/tmp/translations.txt");
  file.deleteFile();
  juce::FileOutputStream output(file);
  for (TranslationSet::const_iterator i = t.begin(); i != t.end(); ++i) {
    output.writeText("\"", false, false);
    output.write(i->first.c_str(), i->first.size());
    output.writeText("\", \"", false, false);
    output.write(i->second.c_str(), i->second.size());
    output.writeText("\"\n", false, false);
  }
}

#endif  // DEBUG

void Trans::translate() const {
  translated_.reset(new String(::juce::translate(original_)));
#ifdef DEBUG
  addTranslation(original_, hint_);
#endif
}

}  // namespace rec

