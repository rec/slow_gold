#include "rec/music/CleanName.h"
#include "rec/base/Arraysize.h"

namespace rec {
namespace music {
namespace {

String removeSuffix(const String& s, const String& suffix) {
  return s.endsWith(suffix) ? s.dropLastCharacters(suffix.length()) : s;
}

template <typename T>
String removeSuffixes(const String& s, T begin, T end) {
  String t = s;
  for (T i = begin; i != end; ++i)
    t = removeSuffix(t, *i);
  return t;
}

String removeIntPrefix(const String& s) {
  int i1, i2, i3;
  for (i1 = 0; i1 < s.length() && isspace(s[i1]); ++i1);
  for (i2 = i1; i2 < s.length() && isdigit(s[i2]); ++i2);
  for (i3 = i2; i3 < s.length() && isspace(s[i3]); ++i3);

  return (i3 <= i2 || i3 > s.length() / 2) ? s : s.substring(i3);
}

}

String cleanName(const String& s) {
  static const char* const suf[] = {".wav", ".mp3", ".aif"};
  return removeIntPrefix(removeSuffixes(s, suf, suf + arraysize(suf)));

}

}  // namespace music
}  // namespace rec
