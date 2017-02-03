#pragma once

#include "rec/base/SampleTime.h"
#include "rec/util/file/CurrentFileBase.h"

namespace rec { namespace gui { class DropFiles; } }

namespace rec {
namespace slow {

class CurrentFile : public util::file::CurrentFileBase {
 public:
  CurrentFile() {}
  const SampleTime length() const { return length_; }
  void saveState() override;

 protected:
  bool determineIfFileEmpty(bool showError) override;
  void nonEmptyFileLoaded() override;
  void afterFileChange(const VirtualFile& newFile) override;
  void beforeFileChange() override;
  void suspend() override;
  void resume() override;
  std::unique_ptr<Message> getFileDescription() override;

  SampleTime length_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(CurrentFile);
};

}  // namespace slow
}  // namespace rec
