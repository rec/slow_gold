#ifndef __REC_SLOW_SLOWTARGET__
#define __REC_SLOW_SLOWTARGET__

#include "rec/command/CommandRecord.h"
#include "rec/slow/HasInstance.h"
#include "rec/util/Listener.h"

namespace rec {

namespace command { class CommandData; }
namespace command { class CommandTarget; }
namespace command { class CommandRecordTable; }

namespace slow {

class Instance;

class Target : public HasInstance,
               public Listener<Enable>,
               public Listener<CommandID> {
 public:
  explicit Target(Instance* i) : HasInstance(i), enable_(ENABLE) {}
  virtual ~Target() {}

  virtual void operator()(CommandID);
  virtual void operator()(Enable);

  virtual bool perform(const InvocationInfo&);

  void addCommandItem(PopupMenu*,
                      CommandID,
                      bool enable,
                      const String& name,
                      int flags);

 private:
  CriticalSection lock_;
  Enable enable_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Target);
};

}  // namespace rec
}  // namespace slow

#endif  // __REC_SLOW_SLOWTARGET__
