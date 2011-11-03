#ifndef __REC_PROTO_ZEROCOPY__
#define __REC_PROTO_ZEROCOPY__

#include <vector>

#include "rec/base/base.h"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/io/zero_copy_stream.h"

using namespace juce;

namespace rec {
namespace util {
namespace file {
namespace zerocopy {

typedef google::protobuf::io::ZeroCopyOutputStream ZeroCopyOutputStream;
typedef google::protobuf::io::ZeroCopyInputStream ZeroCopyInputStream;

template <typename JuceStream, typename Stream>
class Base : public Stream {
 public:
  static const int DEFAULT_SIZE = 1024;
  Base(JuceStream* stream, int size = DEFAULT_SIZE)
      : stream_(stream),
        buffer_(size) {
  }

  void* buffer() { return (void*) &buffer_[0]; }
  int size() const { return buffer_.size(); }
  JuceStream* stream() { return stream_.get(); }
  void flush() { stream_->flush(); }

 protected:
  ptr<JuceStream> stream_;

 private:
  std::vector<uint8> buffer_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Base);
};

typedef Base<FileOutputStream, google::protobuf::io::ZeroCopyOutputStream> OutputBase;

class Output : public OutputBase {
 public:
  Output(const File& file, int size = OutputBase::DEFAULT_SIZE)
      : OutputBase(file.createOutputStream(), size),
        full_(false) {
  }

  virtual ~Output() {
    BackUp(0);
  }

  virtual bool Next(void** data, int* s) {
    BackUp(0);

    *data = buffer();
    *s = size();
    full_ = true;
    return true;
  }

  virtual void BackUp(int count) {
    if (full_) {
      stream_->write(buffer(), size() - count);
      full_ = false;
    }
  }

  virtual int64 ByteCount() const {
    return stream_->getPosition();
  }

 private:
  bool full_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Output);
};

typedef Base<FileInputStream, google::protobuf::io::ZeroCopyInputStream> InputBase;

class Input : public InputBase {
 public:
  Input(const File& file, int s = InputBase::DEFAULT_SIZE)
      : InputBase(file.createInputStream(), s) {
  }

  virtual ~Input() {}

  virtual bool Next(const void** data, int* s) {
    if (stream_->isExhausted())
      return false;

    *s = stream_->read(buffer(), size());
    *data = buffer();
    return true;
  }

  virtual void BackUp(int c) { Skip(-c); }
  virtual bool Skip(int c) {  return stream_->setPosition(ByteCount() + c); }
  virtual int64 ByteCount() const { return stream_->getPosition(); }

 private:
  bool full_;
  DISALLOW_COPY_ASSIGN_AND_EMPTY(Input);
};

}  // namespace zerocopy
}  // namespace file
}  // namespace util
}  // namespace rec

#endif  // __REC_PROTO_ZEROCOPY__
