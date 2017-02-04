#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {
namespace cd {

using StringPair = std::pair<string, string>;

int stripLines(String* data, juce::StringArray* lines);
bool stripLine(String* data, juce::StringArray* lines);

StringPair splitLine(const string& s, int ch);

}  // namespace cd
}  // namespace util
}  // namespace rec
