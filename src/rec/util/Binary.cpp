#include "rec/util/Binary.h"

namespace rec {
namespace util {

using namespace juce;

template <>
String* createBinary(const char* data, int len) {
  return new String(juce::CharPointer_UTF8(data), len);
}

template <>
Drawable* createBinary(const char* data, int len) {
  return Drawable::createFromImageData(data, len);
}

template <>
XmlElement* createBinary(const char* data, int len) {
  return XmlDocument::parse(*ptr<String>(createBinary<String>(data, len)));
}

}  // namespace util
}  // namespace rec

