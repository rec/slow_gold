#include "rec/util/Binary.h"

using namespace juce;

namespace rec {
namespace util {

namespace {

struct BinaryOrFile {
  BinaryOrFile(const char* data, size_t len, const string& name)
      : data_(data), length_(len) {
    static File appFile = File::getSpecialLocation(File::currentApplicationFile)
      .getParentDirectory();
    File file = appFile.getChildFile(str(name));
    if (file.loadFileAsData(memory_)) {
      data_ = static_cast<const char*>(memory_.getData());
      length_ = memory_.getSize();
    }
  }

  const char* data_;
  size_t length_;
  MemoryBlock memory_;
};

}  // namespace

template <>
String* createBinary(const char* data, size_t len, const string& filename) {
  BinaryOrFile b(data, len, filename);
  return new String(juce::CharPointer_UTF8(b.data_), b.length_);
}

template <>
Drawable* createBinary(const char* data, size_t len, const string& filename) {
  BinaryOrFile b(data, len, filename);
  return Drawable::createFromImageData(b.data_, b.length_);
}

template <>
XmlElement* createBinary(const char* data, size_t len, const string& filename) {
  BinaryOrFile b(data, len, filename);
  return XmlDocument::parse(*ptr<String>(createBinary<String>(b.data_, b.length_)));
}

}  // namespace util
}  // namespace rec

