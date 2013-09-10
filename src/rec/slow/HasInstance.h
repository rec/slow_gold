#ifndef __REC_SLOW_HASINSTANCE__
#define __REC_SLOW_HASINSTANCE__

#include "rec/slow/Instance.h"
#include "rec/util/file/VirtualFile.pb.h"
#include "rec/util/LoopPoint.pb.h"

namespace rec {
namespace slow {

class HasInstance {
 public:
  explicit HasInstance(Instance* i = nullptr) : instance_(i) {}

  audio::util::BufferFiller* bufferFiller() { return instance_->bufferFiller_.get(); }
  Components* components() { return instance_->components_.get(); }
  Threads* threads() { return instance_->threads_.get(); }
  audio::source::Player* player() { return instance_->player_.get(); }
  audio::Device* device() { return instance_->device_.get(); }
  CurrentFile* currentFile() { return instance_->currentFile_.get(); }
  CurrentTime* currentTime() { return instance_->currentTime_.get(); }
  app::Window* window() { return instance_->window_; }
  command::CommandRecordTable* commandRecordTable() {
    return instance_->commandRecordTable_.get();
  }
  ApplicationCommandTarget* applicationCommandTarget() {
    return instance_->applicationCommandTarget();
  }
  ApplicationCommandManager* applicationCommandManager() {
    return instance_->applicationCommandManager();
  }
  command::CommandData* commandData() {
    return instance_->commandData_.get();
  }

  const VirtualFile file() const { return instance_->file(); }
  SampleTime time() const { return instance_->time(); }
  SampleTime length() const { return instance_->length(); }
  bool isPlaying() const { return instance_->isPlaying(); }
  bool empty() const { return instance_->empty(); }
  const CriticalSection& lock() const { return instance_->lock_; }

 protected:
  Instance* instance_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(HasInstance);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_HASINSTANCE__
