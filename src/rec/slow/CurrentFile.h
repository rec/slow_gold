#ifndef __REC_SLOW_METHODS_FILEMETHODS__
#define __REC_SLOW_METHODS_FILEMETHODS__

#include "rec/slow/HasInstance.h"
#include "rec/util/Listener.h"
#include "rec/util/file/VirtualFile.pb.h"
#include "rec/widget/waveform/Viewport.pb.h"

namespace rec {

namespace gui { class DropFiles; }

namespace slow {

class CurrentFile : public HasInstance,
                    public Listener<const VirtualFile&>,
                    public Listener<const gui::DropFiles&> {
 public:
  explicit CurrentFile(Instance* i);
  virtual ~CurrentFile();

  // Set the file and change the persistent data.
  virtual void operator()(const gui::DropFiles&);
  virtual void operator()(const VirtualFile& vf) { setFile(vf); }

  const VirtualFile virtualFile() const { Lock l(lock_); return file_; }
  const Samples<44100> length() const { Lock l(lock_); return length_; }
  bool empty() const { return !length_; }
  void setFile(const VirtualFile&);
  void hasStarted() { Lock l(lock_); hasStarted_ = true; }
  const CriticalSection& lock() const { return lock_; }
  static void translateAll();

 private:
  int64 getFileLength();
  void setViewport();

  CriticalSection lock_;

  widget::waveform::Viewport viewport_;
  VirtualFile file_;
  Samples<44100> length_;
  bool initialized_;
  bool hasStarted_;
  DISALLOW_COPY_ASSIGN_AND_LEAKS(CurrentFile);

  friend class Instance;
  friend class FileDataListener;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_METHODS_FILEMETHODS__
