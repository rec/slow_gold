#ifndef __REC_SLOW_METHODS_FILEMETHODS__
#define __REC_SLOW_METHODS_FILEMETHODS__

#include "rec/data/DataFile.h"
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
  virtual void operator()(const VirtualFile& vf);

  const Samples<44100> length() const;
  bool empty() const { return !length(); }
  void setDataFile(data::DataFile);
  void setVirtualFile(const VirtualFile&);
  void setFile(const File&);
  static void translateAll();
  const VirtualFile file() const;

  const CriticalSection& lock() { return lock_; }

 private:
  int64 getFileLength();
  void setViewport();

  CriticalSection lock_;
  widget::waveform::Viewport viewport_;
  ptr<VirtualFile> file_;
  Samples<44100> length_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CurrentFile);

  friend class Instance;
  friend class FileDataListener;
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_METHODS_FILEMETHODS__
