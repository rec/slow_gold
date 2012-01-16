#ifndef __REC_SLOW_METHODS_FILEMETHODS__
#define __REC_SLOW_METHODS_FILEMETHODS__

#include "rec/slow/HasInstance.h"
#include "rec/util/Listener.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {

namespace gui { class DropFiles; }

namespace slow {

class FileDataListener;

class CurrentFile : public HasInstance,
                    public Listener<const VirtualFile&>,
                    public Listener<const gui::DropFiles&> {
 public:
  explicit CurrentFile(Instance* i);
  virtual ~CurrentFile();

  // Set the file and change the persistent data.
  virtual void operator()(const gui::DropFiles&);
  virtual void operator()(const VirtualFile&);

  const VirtualFile virtualFile() const { Lock l(lock_); return file_; }
  const Samples<44100> length() const { Lock l(lock_); return length_; }
  bool empty() const { return empty_; }

 private:
  // Sets the current file but does not change the persistent data.
  void setFile(const VirtualFile&);

  CriticalSection lock_;

  VirtualFile file_;
  Samples<44100> length_;
  ptr<FileDataListener> fileListener_;
  bool initialized_;
  bool empty_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CurrentFile);

  friend class Instance;
  friend class FileDataListener;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_METHODS_FILEMETHODS__
