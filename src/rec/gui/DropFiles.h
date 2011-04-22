#ifndef __REC_GUI_DROPFILES__
#define __REC_GUI_DROPFILES__

#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace gui {

struct DropFiles {
  VirtualFileList files_;
  Component* target_;

  DropFiles() {}
  DropFiles(const VirtualFileList& f, Component* t) : files_(f), target_(t) {}
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_DROPFILES__
