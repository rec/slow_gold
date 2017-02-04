#include "rec/util/partition/Convertors.h"

using namespace juce;

namespace rec {
namespace util {

template <> int getLength(const string& s) { return s.size(); }
template <> int getLength(const String& s) { return s.length(); }

template <> String toLowerCase(const String& s) { return s.toLowerCase(); }

template <> string toLowerCase(const string& s) {
    string t = s;
    for (uint32 i = 0; i < t.size(); ++i)
        t[i] = static_cast<char>(tolower(t[i]));
    return t;
}

template <> void add(Array<int>* list, int x) { list->add(x); }
template <> void add(vector<int>* list, int x) { list->push_back(x); }

template <> const String get(const Array<File>& files, int i) {
    return files[i].getFullPathName();
}

template <> const String get(const vector<string>& files, int i) {
    return str(files[i]);
}

String getName(const File& f) { return f.getFileName();  }
String getName(const string& v) { return str(v); }

}  // namespace util
}  // namespace rec
