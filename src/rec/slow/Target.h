#ifndef __REC_SLOW_SLOWTARGET__
#define __REC_SLOW_SLOWTARGET__

#include "rec/command/Command.pb.h"
#include "rec/slow/HasInstance.h"
#include "rec/command/TargetManager.h"

namespace rec {

namespace command { class MidiCommandMap; }

namespace slow {

class Instance;

class Target : public command::TargetManager, public HasInstance {
 public:
  explicit Target(Instance* instance);
  virtual ~Target();

  void addCommands();
  command::MidiCommandMap* midiCommandMap() { return midiCommandMap_.get(); }

 private:
  ptr<command::MidiCommandMap> midiCommandMap_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Target);
};

}  // namespace rec
}  // namespace slow

#endif  // __REC_SLOW_SLOWTARGET__
