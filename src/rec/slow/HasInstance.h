#ifndef __REC_SLOW_HASINSTANCE__
#define __REC_SLOW_HASINSTANCE__

#include "rec/slow/Instance.h"
#include "rec/util/file/VirtualFile.pb.h"
#include "rec/util/LoopPoint.pb.h"

namespace rec {
namespace slow {

class HasInstance {
 public:
  explicit HasInstance(Instance* i = NULL) : instance_(i) {}

  audio::util::BufferFiller* bufferFiller() { return instance_->bufferFiller_.get(); }
  Components* components() { return instance_->components_.get(); }
  Target* target() { return instance_->target_.get(); }
  Threads* threads() { return instance_->threads_.get(); }
  audio::source::Player* player() { return instance_->player_.get(); }
  audio::Device* device() { return instance_->device_.get(); }
  CurrentFile* currentFile() { return instance_->currentFile_.get(); }
  CurrentTime* currentTime() { return instance_->currentTime_.get(); }
  Menus* menus() { return instance_->menus_.get(); }
  SlowWindow* window() { return instance_->window_; }

  const VirtualFile file() const { return instance_->file(); }
  Samples<44100> time() const { return instance_->time(); }
  Samples<44100> length() const { return instance_->length(); }
  bool isPlaying() const { return instance_->isPlaying(); }

 protected:
  Instance* instance_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(HasInstance);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_HASINSTANCE__
