#include <set>

#include "rec/util/Copy.h"
#include "rec/base/Trans.pb.h"

using namespace juce;

namespace rec {

#if JUCE_DEBUG && JUCE_MAC

namespace {

const char* const TRANSLATION_FILE =
  "/development/rec/text/en-incoming-rec.TranslatedStrings.def";

string cleanFile(const String& file) {
  String f = file;
  int i = file.indexOf("/src/rec/");
  if (i >= 0)
    f = f.substring(i + 5);
  return str(f);
}

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

void registerTranslation(const TranslatedString& s) {
  translations()->insert(s);
}

void write(FileOutputStream* output, const String& s) {
  output->writeText(s, false, false);
}

TranslatedStrings getTranslatedStrings() {
  const TranslationSet& tr = *translations();
  TranslatedStrings strings;
  for (TranslationSet::const_iterator i = tr.begin(); i != tr.end(); ++i)
    strings.add_str()->CopyFrom(*i);
  return strings;
}

}  // namespace

void Trans::dumpAll() {
  LOG(INFO) << "Dumping translations " << translations()->size();
  copy::copy(getTranslatedStrings(), File(TRANSLATION_FILE));
}

#endif  // DEBUG

Trans::Trans(const char* original)
    : string_(new TranslatedString),
      translationRegistered_(false),
      language_(Internationalization::NONE) {
  string_->set_original(original);
  check(string_->original());
}

Trans::Trans(const char* original, const char* file, int line)
    : string_(new TranslatedString),
      translationRegistered_(false),
      language_(Internationalization::NONE) {
  string_->set_original(original);
  string_->set_file(cleanFile(file));
  string_->set_line(line);
  check(string_->original());
}

Trans::Trans(const String& original, const char* file, int line)
    : string_(new TranslatedString),
      translationRegistered_(false),
      language_(Internationalization::NONE) {
  string_->set_original(str(original));
  string_->set_file(cleanFile(file));
  string_->set_line(line);
  check(string_->original());
}

Trans::Trans(const char* original, const char* hint, const char* file, int line)
    : string_(new TranslatedString),
      translationRegistered_(false),
      language_(Internationalization::NONE) {
  string_->set_original(original);
  string_->set_file(cleanFile(file));
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

Trans::operator String() const {
  registerTranslation();
  return str(string_->original());
}

void Trans::registerTranslation() const {
  Lock l(lock_);
  if (!translationRegistered_) {
    translationRegistered_ = true;
#if JUCE_DEBUG && JUCE_MAC
    rec::registerTranslation(*string_);
#endif
  }
}

}  // namespace rec
