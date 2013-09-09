#ifndef __REC_PROGRAM_PROGRAMBASE__
#define __REC_PROGRAM_PROGRAMBASE__

#include <unordered_map>

#include "rec/Program/Program.h"

namespace rec {
namespace program {

class ProgramBase : public Program {
 public:
  ProgramBase();
  virtual ~ProgramBase();

  void addCallback(CommandID, unique_ptr<Callback>) override;
  Callback* getCallback(CommandID) const override;
  bool hasProperty(const string& name) const override;
  CallbackMap* getCallbackMap() override { return &callbackMap_; }
  bool isEnabled() const override;
  void setEnabled(bool) override;

 protected:
  CriticalSection lock_;

 private:
  bool enabled_;
  CallbackMap callbackMap_;
};

}  // namespace program
}  // namespace rec

#endif  // __REC_PROGRAM_PROGRAMBASE__
