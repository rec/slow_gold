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
               public Listener<None>,
               public Listener<CommandID>,
               public Listener<bool>,
               public Broadcaster<None> {
 public:
  explicit Target(Instance* instance);
  virtual ~Target();

  void addCommands();

  virtual void operator()(None);
  virtual void operator()(CommandID);
  virtual void operator()(bool);

  virtual bool perform(const InvocationInfo&);

  void addCallback(CommandID id,
                   Callback* cb,
                   const String& name,
                   const String& category,
                   const String& desc);

  void addCommandItem(PopupMenu*,
                      CommandID,
                      bool enable,
                      const String& name,
                      int flags);

 private:
  CriticalSection lock_;
  bool disabled_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Target);
};

}  // namespace rec
}  // namespace slow

#endif  // __REC_SLOW_SLOWTARGET__
