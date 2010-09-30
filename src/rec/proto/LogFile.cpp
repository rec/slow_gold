#include "rec/proto/LogFile.h"

#include "google/protobuf/message.h"
#include "rec/proto/ZeroCopy.h"

namespace rec {
namespace proto {
namespace logfile {

typedef google::protobuf::io::CodedOutputStream CodedOutputStream;
typedef google::protobuf::io::CodedInputStream CodedInputStream;

template <typename Zero, typename Coded>
class Base {
 public:
  Base(const File &file) : zero_(file), coded_(&zero_) {}

 protected:
  Zero zero_;
  Coded coded_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Base);
};


typedef Base<zerocopy::Input, CodedInputStream> InputBase;

class InputImpl : public InputBase {
 public:
  explicit InputImpl(const File& file) : InputBase(file) {}

  bool read(Message* message) {
    uint64 size;
    string s;
    return coded_.ReadVarint64(&size) &&
      coded_.ReadString(&s, size) &&
      message->ParseFromString(s);
  }
};

typedef Base<zerocopy::Output, CodedOutputStream> OutputBase;

class OutputImpl : public OutputBase {
 public:
  explicit OutputImpl(const File& file) : OutputBase(file) {}

  void write(const Message& message) {
    string s;
    message.SerializeToString(&s);
    coded_.WriteVarint64(s.size());
    coded_.WriteString(s);
  }

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(OutputImpl);
};

Input::Input(const File& file) : impl_(new InputImpl(file)) {}
Input::~Input() {}
bool Input::read(Message* message) { return impl_->read(message); }

Output::Output(const File& file) : impl_(new OutputImpl(file)) {}
Output::~Output() {}
void Output::write(const Message& message) { impl_->write(message); }

}  // namespace logfile
}  // namespace proto
}  // namespace rec
