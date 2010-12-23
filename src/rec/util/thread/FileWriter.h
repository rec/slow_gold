#ifndef __REC_UTIL_THREAD_FILEWRITER__
#define __REC_UTIL_THREAD_FILEWRITER__

#include "rec/util/thread/Trash.h"

namespace rec {
namespace util {
namespace thread {

class FileWriter : public Thread {
 public:
  FileWriter(const File& file) : Thread("FileWriter"), file_(file) {}
  MemoryBlock* memory() { return &memory_; }

  virtual void run() {
    string file = file_.getFullPathName().toCString();
    if (!file_.getParentDirectory().createDirectory()) {
      LOG(ERROR) << "Can't make dir " << file;

    } else if (!file_.deleteFile()) {
      LOG(ERROR) << "Can't delete file " << file;

    } else {
      ::ptr<OutputStream> out(file_.createOutputStream());
      if (out) {
        (*out) << memory_;
        DLOG(INFO) << "Saved to file " << file;
      } else {
        LOG(ERROR) << "Can't create file " << file;
      }
    }

    trash::discard(this);
  }

 private:
  MemoryBlock memory_;
  const File file_;
  DISALLOW_COPY_AND_ASSIGN(FileWriter);
};


}  // namespace thread
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_THREAD_FILEWRITER__
