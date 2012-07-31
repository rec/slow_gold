#include <set>

#include "rec/util/Copy.h"
#include "rec/base/Trans.pb.h"

namespace rec {

Trans::Trans(const char* original) : string_(new TranslatedString) {
  string_->set_original(original);
  check(string_->original());
}

Trans::Trans(const char* original, const char* file, int line)
    : string_(new TranslatedString) {
  string_->set_original(original);
  string_->set_file(file);
  string_->set_line(line);
  check(string_->original());
}

Trans::Trans(const String& original, const char* file, int line)
    : string_(new TranslatedString) {
  string_->set_original(str(original));
  string_->set_file(file);
  string_->set_line(line);
  check(string_->original());
}

Trans::Trans(const char* original, const char* hint, const char* file, int line)
    : string_(new TranslatedString) {
  string_->set_original(original);
  string_->set_file(file);
  string_->set_line(line);
  string_->set_hint(hint);
  check(string_->original());
  check(string_->hint());
}

Trans::~Trans() {
#if JUCE_DEBUG && JUCE_MAC
  using namespace std;
  if (string_->translation().empty())
    cerr << "Didn't translate " << string_->ShortDebugString();
#endif
}

void Trans::check(const string& st) {
  String s = str(st);
  DCHECK_GT(s.length(), 0);
  DCHECK(!s.containsChar('\n')) << str(s);
  DCHECK(!s.containsChar('\r')) << str(s);
  DCHECK(!s.containsChar('\t')) << str(s);
  DCHECK(!isspace(s[0])) << str(s);
  DCHECK(!isspace(s[s.length() - 1])) << str(s);
}

using namespace juce;

#if JUCE_DEBUG && JUCE_MAC

namespace {

struct Compare {
  bool operator()(const TranslatedString& x, const TranslatedString& y) const {
    int c = str(x.original()).compareIgnoreCase(str(y.original()));
    if (!c)
      c = str(x.hint()).compareIgnoreCase(str(y.hint()));
    return c < 0;
  }
};

typedef std::set<TranslatedString, Compare> TranslationSet;

TranslationSet* translations() {
  static TranslationSet s;
  return &s;
}

void addTranslation(const TranslatedString& s) {
  translations()->insert(s);
}

void write(FileOutputStream* output, const String& s) {
  output->writeText(s, false, false);
}

TranslatedStrings getTranslatedStrings(const TranslationSet& tr) {
  TranslatedStrings strings;
  for (TranslationSet::const_iterator i = tr.begin(); i != tr.end(); ++i)
    strings.add_str()->CopyFrom(*i);
  return strings;
}

}  // namespace

void Trans::dumpAll() {
  LOG(INFO) << "Dumping translations " << translations()->size();
  File file("/tmp/translations.txt");
  TranslatedStrings strings = getTranslatedStrings(*translations());
  copy::copy(strings, &file);
}

#endif  // DEBUG

Trans::operator String() const {
  if (!string_->has_translation())
    translate();
  return str(string_->translation());
}


void Trans::translate() const {
  String s(str(string_->original()));
  string_->set_translation(str(juce::translate(s)));

#if JUCE_DEBUG && JUCE_MAC
  addTranslation(*string_);
#endif
}

}  // namespace rec

