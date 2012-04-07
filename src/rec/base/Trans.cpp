#include <set>

#include "rec/base/base.h"

namespace rec {

using namespace juce;

#ifdef DEBUG

namespace {

typedef std::pair<String, String> StringPair;
typedef std::set<StringPair> TranslationSet;

TranslationSet* translations() {
  static TranslationSet s;
  return &s;
}

String fix(const String& s) {
  return s.replace("\\", "\\\\").replace("\"", "\\\"");
}

void addTranslation(const String& s, const String& hint) {
  translations()->insert(std::make_pair(fix(s), fix(hint)));
}

void write(FileOutputStream* output, const String& s) {
  output->writeText(s, false, false);
}

}  // namespace

void Trans::dumpAll() {
  DLOG(INFO) << "Dumping translations " << translations()->size();

  const TranslationSet& t = *translations();
  File file("/tmp/translations.txt");
  file.deleteFile();
  juce::FileOutputStream output(file);
  for (TranslationSet::const_iterator i = t.begin(); i != t.end(); ++i) {
    write(&output, "- [\"");
    write(&output, i->first);
    write(&output, "\", \"");
    write(&output, i->second);
    write(&output, "\"]\n");
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

