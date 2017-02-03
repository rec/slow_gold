#include "rec/util/Binary.h"
#include "BinaryData.h"

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

void binaryProtoMerged(const string& s, Message* message) {
    BinaryNames names;
    copy::copy(s, &names);

    for (auto& name: names.name())
        copy::merge(getNamedResource(name + "_def"), message);
}

string getNamedResource(const string& name) {
    int dataSize;
    const char* resource = BinaryData::getNamedResource(name.c_str(), dataSize);
    return string(resource, dataSize);
}

template <>
String* construct(const string& s) {
    return new String(str(s));
}

template <>
Drawable* construct(const string& s) {
    return Drawable::createFromImageData(s.data(), s.size());
}

template <>
XmlElement* construct(const string& s) {
    return XmlDocument::parse(str(s));
}

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
    auto binary = createBinary<String>(b.data_, b.length_);
    return XmlDocument::parse(*std::unique_ptr<String>(binary));
}

}  // namespace util
}  // namespace rec
