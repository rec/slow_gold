#include "rec/util/partition/Convertors.h"

using namespace juce;
using std::vector;

namespace rec {
namespace util {
namespace partition {

template <> int getLength(const string& s) { return s.size(); }
template <> int getLength(const String& s) { return s.length(); }

template <> String toLowerCase(const String& s) { return s.toLowerCase(); }

template <> string toLowerCase(const string& s) {
  string t = s;
  for (int i = 0; i < t.size(); ++i)
    t[i] = tolower(t[i]);
  return t;
}

template <> void add(Array<int>* list, int x) { list->add(x); }
template <> void add(vector<int>* list, int x) { list->push_back(x); }

template <> const String& get(const Array<File>& files, int i) {
  return files[i].getFullPathName();
}

template <> const string& get(const vector<string>& files, int i) {
  return files[i];
}

String getName(const File& f) { return f.getFileName();  }
string getName(const string& v) { return v; }

}  // namespace partition
}  // namespace util
}  // namespace rec
