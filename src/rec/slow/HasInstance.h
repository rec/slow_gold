#ifndef __REC_SLOW_HASINSTANCE__
#define __REC_SLOW_HASINSTANCE__

#include "rec/slow/Instance.h"
#include "rec/util/file/VirtualFile.pb.h"

namespace rec {
namespace slow {

class HasInstance {
 public:
  explicit HasInstance(Instance* i = NULL) : instance_(i) {}

  Components* components() { return instance_->components_.get(); }
  Model* model() { return instance_->model_.get(); }
  Target* target() { return instance_->target_.get(); }
  Threads* threads() { return instance_->threads_.get(); }
  audio::source::Player* player() { return instance_->player_.get(); }
  audio::Device* device() { return instance_->device_.get(); }
  CurrentFile* currentFile() { return instance_->currentFile_.get(); }
  const VirtualFile file() const { return instance_->file(); }

 protected:
  Instance* instance_;

  DISALLOW_COPY_AND_ASSIGN(HasInstance);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_HASINSTANCE__
