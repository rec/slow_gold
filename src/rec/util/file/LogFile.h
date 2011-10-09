#ifndef __REC_PROTO_LOGFILE__
#define __REC_PROTO_LOGFILE__

#include "rec/base/base.h"

namespace rec {
namespace proto {
namespace logfile {

class InputImpl;
class OutputImpl;

class Input {
 public:
  explicit Input(const File& file);
  ~Input();

  bool read(Message* message);

 private:
  ptr<InputImpl> impl_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Input);
};

class Output {
 public:
  explicit Output(const File& file);
  ~Output();

  void write(const Message& message);

 private:
  ptr<OutputImpl> impl_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Output);
};

}  // namespace logfile
}  // namespace proto
}  // namespace rec

#endif  // __REC_PROTO_LOGFILE__
