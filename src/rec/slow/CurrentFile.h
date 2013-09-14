#ifndef __REC_SLOW_METHODS_FILEMETHODS__
#define __REC_SLOW_METHODS_FILEMETHODS__

#include "rec/base/SampleTime.h"
#include "rec/util/Listener.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec { namespace gui { class DropFiles; } }

namespace rec {
namespace slow {

class CurrentFile : public Listener<const VirtualFile&>,
                    public Listener<const gui::DropFiles&> {
 public:
  CurrentFile() {}
  virtual ~CurrentFile() {}

  // Set the file and change the persistent data.
  virtual void operator()(const gui::DropFiles&);
  virtual void operator()(const VirtualFile& vf);

  bool empty() const { return !length(); }

  void setVirtualFile(const VirtualFile&, bool showError);
  void setFile(const File&, bool showError = true);
  const VirtualFile file() const;

  const CriticalSection& lock() { return lock_; }

  // derived
  const SampleTime length() const;

 protected:
  bool determineIfFileEmpty(bool showError);
  void nonEmptyFileLoaded();
  void continueLoading(bool showError);
  void afterFileChange(const VirtualFile& newFile);
  void beforeFileChange();
  void suspend();
  void resume();
  unique_ptr<Message> getFileDescription();

  CriticalSection lock_;
  VirtualFile file_;
  SampleTime length_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CurrentFile);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_METHODS_FILEMETHODS__
