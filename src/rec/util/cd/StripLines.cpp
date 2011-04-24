#include "rec/util/cd/StripLines.h"

using namespace juce;

namespace rec {
namespace util {
namespace cd {

int stripLines(String* data, StringArray* lines) {
  int i = 0;
  for (; stripLine(data, lines); ++i);
  return i;
}

bool stripLine(String* data, StringArray* lines) {
#ifdef NEW_JUCE
  const juce_wchar* begin = data->toWideCharPointer();
#else
  const juce_wchar* begin = *data;
#endif
  for (const juce_wchar* i = begin; *i; ++i) {
    const juce_wchar* end = NULL;
    if (*i == '\n')
      end = i;

    if (*i == '\r')
      end = (*(i + 1) == '\n') ? i + 1 : i;

    if (end) {
      lines->add(String(begin, i - begin));
      (*data) = data->substring(end - begin + 1);
      return true;
    }
  }
  return false;
}

StringPair splitLine(const string& s, int ch) {
  string first = s, second;
  string sep = "   ";
  sep[1] = ch;
  int loc = s.find(sep);
  if (loc != -1) {
    first = s.substr(0, loc);
    second = s.substr(loc + sep.size());
  }
  return std::make_pair(first, second);
}

}  // namespace cd
}  // namespace util
}  // namespace rec
