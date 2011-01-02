#include "rec/util/Compare.h"
#include "rec/util/partition/Convertors.h"

using namespace juce;
using std::vector;

namespace rec {
namespace util {

bool isASCII(int c) { return c > 0 && c <= 0xFF; }

bool isPunctuation(int c) {
  return isASCII(c) &&
    (c < '0' || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || c > 'z');
}

int compareChars(int c, int d) {
  bool pc = isPunctuation(c);
  bool pd = isPunctuation(d);

  return (pc == pd) ? (tolower(c) - tolower(d)) : (pc ? -1 : 1);
}

template <typename Str>
int compareStrings(const Str& x, const Str& y) {
  for (int i = 0; ; ++i) {
    if (i >= getLength(x))
      return i >= getLength(y) ? 0 : -1;

    if (i >= getLength(y))
      return 1;

    if (int cmp = compareChars(x[i], y[i]))
      return cmp;
  }
}

template <typename Str>
int indexOfDifference(const Str& s, const Str& t) {
  int slength = getLength(s);
  int tlength = getLength(t);
  int min = juce::jmin(slength, tlength);
  for (int i = 0; i < min; ++i) {
    if (compareChars(s[i], t[i]))
      return i;
  }
  return (min == juce::jmax(slength, tlength)) ? -1 : min;
}

template <typename Collection>
int indexOfDifference(const Collection& items, const int i) {
  return indexOfDifference(toLowerCase(getName(items[i - 1])),
                           toLowerCase(getName(items[i])));
}

bool compareFiles(const File& f, const File& g) {
  return compareStrings(f.getFileName(), g.getFileName()) < 0;
}

template int compareStrings(const String& x, const String& y);

template int indexOfDifference(const Array<File>& items, const int i);
template int indexOfDifference(const vector<string>& items, const int i);
template int indexOfDifference(const String& s, const String& t);

}  // namespace util
}  // namespace rec
