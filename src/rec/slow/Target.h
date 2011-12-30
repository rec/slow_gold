#ifndef __REC_SLOW_SLOWTARGET__
#define __REC_SLOW_SLOWTARGET__

#include "rec/slow/HasInstance.h"
#include "rec/command/TargetManager.h"

namespace rec {

namespace command { class MidiCommandMap; }

namespace slow {

class Instance;

class Target : public HasInstance, public Listener<None> {
 public:
  explicit Target(Instance* instance);
  virtual ~Target();

  command::MidiCommandMap* midiCommandMap() { return midiCommandMap_.get(); }
  command::TargetManager* targetManager() { return &manager_; }
  void addCommands();

  virtual void operator()(None);

 private:
  command::TargetManager manager_;
  ptr<command::MidiCommandMap> midiCommandMap_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Target);
};

}  // namespace rec
}  // namespace slow

#endif  // __REC_SLOW_SLOWTARGET__
