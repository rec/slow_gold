#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace cd {

typedef std::pair<string, string> StringPair;

int stripLines(String* data, juce::StringArray* lines);
bool stripLine(String* data, juce::StringArray* lines);

StringPair splitLine(const string& s, int ch);

}  // namespace cd
}  // namespace util
}  // namespace rec

