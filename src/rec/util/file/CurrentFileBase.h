#ifndef __REC_UTIL_FILE_CURRENTFILEBASE__
#define __REC_UTIL_FILE_CURRENTFILEBASE__

#include "rec/util/Listener.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec { namespace gui { class DropFiles; } }

namespace rec {
namespace util {
namespace file {

class CurrentFileBase : public Listener<const VirtualFile&>,
                        public Listener<const gui::DropFiles&> {
 public:
  CurrentFileBase() : empty_(true) {}
  virtual ~CurrentFileBase() {}

  // Set the file and change the persistent data.
  virtual void operator()(const gui::DropFiles&);
  virtual void operator()(const VirtualFile& vf);

  bool empty() const { return empty_; }

  void setVirtualFile(const VirtualFile&, bool showError);
  void setFile(const File&, bool showError = true);
  const VirtualFile file() const { return file_; }
  virtual void saveState() = 0;

 protected:
  virtual bool determineIfFileEmpty(bool showError) = 0;
  virtual void nonEmptyFileLoaded() = 0;
  virtual void afterFileChange(const VirtualFile& newFile) = 0;
  virtual void beforeFileChange() = 0;
  virtual void suspend() = 0;
  virtual void resume() = 0;
  virtual unique_ptr<Message> getFileDescription() = 0;

  bool empty_;
  CriticalSection lock_;
  VirtualFile file_;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(CurrentFileBase);
};

}  // namespace file
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_FILE_CURRENTFILEBASE__
