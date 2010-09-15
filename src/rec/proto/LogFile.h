#ifndef __REC_PROTO_LOGFILE__
#define __REC_PROTO_LOGFILE__

#include "google/protobuf/message.h"
#include "rec/base/basictypes.h"
#include "rec/proto/ZeroCopy.h"

namespace rec {
namespace proto {
namespace logfile {

template <typename Zero, typename Coded>
class Base {
 public:
  Base(const File &file) : zero_(file), coded_(&zero_) {}

 protected:
  Zero zero_;
  Coded coded_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Base);
};

typedef Base<zerocopy::Output, google::protobuf::io::CodedOutputStream> OutputBase;

class Output : public OutputBase {
 public:
  Output(const File& file) : OutputBase(file) {}

  void write(const google::protobuf::Message& message) {
    std::string s;
    message.SerializeToString(&s);
    coded_.WriteVarint64(s.size());
    coded_.WriteString(s);
  }
};

typedef Base<zerocopy::Input, google::protobuf::io::CodedInputStream> InputBase;

class Input : public InputBase {
 public:
  Input(const File& file) : InputBase(file) {}

  bool read(google::protobuf::Message* message) {
    uint64 size;
    std::string s;
    return coded_.ReadVarint64(&size) &&
      coded_.ReadString(&s, size) &&
      message->ParseFromString(s);
  }
};

}  // namespace logfile
}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_LOGFILE__
