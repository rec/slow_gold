#ifndef __REC_PROTO_LOGFILE__
#define __REC_PROTO_LOGFILE__

#include "rec/util/Copy.h"

namespace rec {
namespace util {
namespace file {

class InputImpl;
class OutputImpl;

class Input {
 public:
  explicit Input(const File& file, 
                 copy::Style readable = copy::READABLE);
  ~Input();

  bool read(Message* message);

 private:
  ptr<InputImpl> impl_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Input);
};

class Output {
 public:
  explicit Output(const File& file, 
                  copy::Style readable = copy::READABLE);
  ~Output();

  void write(const Message& message);
  void flush();

 private:
  ptr<OutputImpl> impl_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Output);
};

}  // namespace file
}  // namespace util
}  // namespace rec

#endif  // __REC_PROTO_LOGFILE__
