#include "rec/data/Binary.h"

namespace rec {
namespace data {

using namespace juce;

template <>
String* create(const char* data, int len) {
  return new String(juce::CharPointer_UTF8(data), len);
}

template <>
Drawable* create(const char* data, int len) {
  return Drawable::createFromImageData(data, len);
}

template <>
XmlElement* create(const char* data, int len) {
  return XmlDocument::parse(*ptr<String>(create<String>(data, len)));
}

}  // namespace data
}  // namespace rec
