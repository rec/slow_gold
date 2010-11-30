#include "rec/util/cd/StripLines.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace util {
namespace cd {

int stripLines(String* data, StringArray* lines) {
  int i = 0;
  for (; stripLine(data, lines); ++i);
  return i;
}

bool stripLine(String* data, StringArray* lines) {
  const juce_wchar* begin = *data;
  for (const juce_wchar* i = begin; *i; ++i) {
    char juce_wchar* end = NULL;
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

}  // namespace cd
}  // namespace util
}  // namespace rec
