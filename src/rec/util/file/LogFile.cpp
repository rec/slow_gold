#include <google/protobuf/text_format.h>

#include "rec/util/file/LogFile.h"

#include "google/protobuf/message.h"
#include "rec/util/file/ZeroCopy.h"

using namespace juce;

namespace rec {
namespace util {
namespace file {

using namespace google::protobuf::io;

using copy::Style;
using google::protobuf::TextFormat;

template <typename Zero, typename Coded>
class Base {
  public:
    Base(const File &file) : zero_(file), coded_(&zero_) {}

  protected:
    Zero zero_;
    Coded coded_;

    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Base);
};

typedef Base<zerocopy::Input, CodedInputStream> InputBase;

class InputImpl : public InputBase {
  public:
    explicit InputImpl(const File& file, Style style)
            : InputBase(file), style_(style) {
    }

    bool read(Message* message) {
        uint64 size;
        string s;

        // This won't handle extremely long strings.
        return coded_.ReadVarint64(&size) &&
            coded_.ReadString(&s, static_cast<int>(size)) &&
            copy::copy(s, message, style_);
    }

  private:
    const Style style_;

    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(InputImpl);
};

typedef Base<zerocopy::Output, CodedOutputStream> OutputBase;

class OutputImpl : public OutputBase {
  public:
    explicit OutputImpl(const File& file, Style style)
            : OutputBase(file), style_(style) {
    }

    void write(const Message& message) {
        string s;

        copy::copy(message, &s, style_);
        coded_.WriteVarint64(s.size());
        coded_.WriteString(s);
    }

    void flush() {
        zero_.flush();
    }

  private:
    const Style style_;

    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(OutputImpl);
};

Input::Input(const File& f, Style style)
        : impl_(new InputImpl(f, style)) {
}

Input::~Input() {
}

bool Input::read(Message* m) {
    return impl_->read(m);
}

Output::Output(const File& f, Style style)
    : impl_(new OutputImpl(f, style)) {
}

Output::~Output() {
}

void Output::write(const Message& m) {
    impl_->write(m);
}

void Output::flush() {
    impl_->flush();
}

}  // namespace file
}  // namespace util
}  // namespace rec
