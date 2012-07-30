#include <set>

#include "rec/base/base.h"

namespace rec {

using namespace juce;

#if JUCE_DEBUG && JUCE_MAC

namespace {

struct CompareString {
  bool operator()(const String& x, const String& y) {
    return x.compareIgnoreCase(y);
  }
};

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

using namespace juce;

var* getVariantFromTranslations(const TranslationSet& tr) {
  ptr<var> v(new var);
  for (TranslationSet::const_iterator i = tr.begin(); i != tr.end(); ++i) {
    var v2;
    v2.append(i->first);
    if (!i->second.isEmpty())
      v2.append(i->second);
    v->append(v2);
  }
  return v.transfer();
}

}  // namespace

Trans::~Trans() {
#if JUCE_DEBUG && JUCE_MAC
  using namespace std;
  if (!translated_)
    cerr << "Didn't xlate \"" << original_ << "\", " << hint_ << "\n" << flush;
#endif
}

void Trans::dumpAll() {
  LOG(INFO) << "Dumping translations " << translations()->size();

  File file("/tmp/translations.txt");
  file.deleteFile();
  juce::FileOutputStream output(file);
  ptr<var> v(getVariantFromTranslations(*translations()));
  JSON::writeToStream(output, *v);
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
  DCHECK(!s.containsChar('\n')) << str(s);
  DCHECK(!s.containsChar('\r')) << str(s);
  DCHECK(!s.containsChar('\t')) << str(s);
  // DCHECK(!isspace(s[0])) << str(s);
  // DCHECK(!isspace(s[s.length() - 1])) << str(s);
}


void Trans::translate() const {
  translated_.reset(new String(::juce::translate(original_)));
#if JUCE_DEBUG && JUCE_MAC
  addTranslation(original_, hint_);
#endif
}

}  // namespace rec

