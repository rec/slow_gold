#include <memory>
#include <set>

#include "rec/util/Copy.h"
#include "rec/base/Trans.pb.h"
#include "rec/translation/TranslationTables.h"

using namespace juce;

TRAN(OK, "OK");
TRAN(CANCEL, "Cancel");

namespace rec {

namespace {

string cleanFile(const String& file) {
    String f = file;
    int i = file.indexOf("/src/rec/");
    if (i >= 0)
        f = f.substring(i + 5);
    return str(f);
}

#if JUCE_DEBUG && JUCE_MAC

const char* const TRANSLATION_FILE =
    "/development/rec/text/en-incoming-TranslatedStrings.def";

struct Compare {
    bool operator()(const TranslatedString& x, const TranslatedString& y) const {
        int c = str(x.original()).compareIgnoreCase(str(y.original()));
        if (!c)
            c = str(x.hint()).compareIgnoreCase(str(y.hint()));
        return c < 0;
    }
};

typedef std::set<TranslatedString, Compare> TranslationSet;
typedef vector<TranslatedString> TranslationList;

TranslationList* translationList() {
    static TranslationList s;
    return &s;
}

void registerTranslation(const TranslatedString& s) {
    translationList()->push_back(s);
}

#if 0
void write(FileOutputStream* output, const String& s) {
    output->writeText(s, false, false);
}
#endif


TranslatedStrings getTranslatedStrings() {
    TranslationSet ts(translationList()->begin(), translationList()->end());
    LOG(INFO) << "Dumping translations " << ts.size();
    TranslatedStrings strings;
    for (TranslationSet::const_iterator i = ts.begin(); i != ts.end(); ++i)
        strings.add_str()->CopyFrom(*i);
    return strings;
}

#endif  // DEBUG

}  // namespace

#if JUCE_DEBUG && JUCE_MAC

void Trans::dumpAll() {
    copy::copy(getTranslatedStrings(), File(TRANSLATION_FILE));
}

#endif  // DEBUG


Trans::Trans(const string& original)
        : string_(new TranslatedString),
            language_(app::AppSettings::NONE) {
    string_->set_original(original);
    check(string_->original());
    registerTranslation();
}

Trans::Trans(const char* original, const char* file, int line)
        : string_(new TranslatedString),
            language_(app::AppSettings::NONE) {
    string_->set_original(original);
    string_->set_file(cleanFile(file));
    string_->set_line(line);
    check(string_->original());
    registerTranslation();
}

Trans::Trans(const String& original, const char* file, int line)
        : string_(new TranslatedString),
            language_(app::AppSettings::NONE) {
    string_->set_original(str(original));
    string_->set_file(cleanFile(file));
    string_->set_line(line);
    check(string_->original());
    registerTranslation();
}

Trans::Trans(const char* original, const char* hint, const char* file, int line)
        : string_(new TranslatedString),
            language_(app::AppSettings::NONE) {
    string_->set_original(original);
    string_->set_file(cleanFile(file));
    string_->set_line(line);
    string_->set_hint(hint);
    check(string_->original());
    check(string_->hint());
    registerTranslation();
  }

Trans::~Trans() {
#if JUCE_DEBUG && JUCE_MAC
    using namespace std;
    if (string_->translation().empty())
        cerr << "Didn't translate " << string_->ShortDebugString() << std::endl << std::flush;
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
    string s = translation::translate(*string_);
    return str(s);
}

void Trans::registerTranslation() const {
#if JUCE_DEBUG && JUCE_MAC
    rec::registerTranslation(*string_);
#endif
    string_->set_translation(string_->original());
}

}  // namespace rec
