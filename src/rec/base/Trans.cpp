#include <set>

#include "rec/base/base.h"

namespace rec {

using namespace juce;

#if JUCE_DEBUG && JUCE_MAC

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
  LOG(INFO) << "Dumping translations " << translations()->size();

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

Trans::operator const String&() const {
  if (!translated_)
    translate();
  return *translated_;
}

Trans::Trans(const char* o) : original_(CharPointer_UTF8(o)) {
  check(original_);
}

Trans::Trans(const String& s) : original_(s) {
  check(original_);
}

Trans::Trans(const char* o, const char* h)
    : original_(CharPointer_UTF8(o)),
      hint_(CharPointer_UTF8(h)) {
  check(original_);
  check(hint_);
}

void Trans::check(const String& s) {
  DCHECK_GT(s.length(), 0);
  // DCHECK(!s.containsChar('\n')) << str(s);
  DCHECK(!s.containsChar('\r')) << str(s);
  DCHECK(!s.containsChar('\t')) << str(s);
  DCHECK(!isspace(s[0])) << str(s);
  DCHECK(!isspace(s[s.length() - 1])) << str(s);
}


void Trans::translate() const {
  translated_.reset(new String(::juce::translate(original_)));
#if JUCE_DEBUG && JUCE_MAC
  addTranslation(original_, hint_);
#endif
}

}  // namespace rec

