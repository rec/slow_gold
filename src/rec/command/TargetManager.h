#ifndef __REC_SLOW_COMMANDTARGET__
#define __REC_SLOW_COMMANDTARGET__

#include <map>

#include "rec/command/CommandRecord.h"
#include "rec/command/CommandData.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/command/CommandItemSetter.h"
#include "rec/command/CommandRecordTable.h"
#include "rec/util/Listener.h"
#include "rec/util/STL.h"
#include "rec/util/thread/Callback.h"

namespace rec {
namespace command {

// An implementation of ApplicationCommandTargetManager that lets you register commands
// with a callback.
class TargetManager : public Listener<CommandID>,
                      public Listener<bool>,
                      public Broadcaster<None> {
 public:
  TargetManager(CommandData*, ApplicationCommandManager*);
  virtual ~TargetManager();

  void addCommands();

  bool invokeDirectly(CommandID commandID, bool asynchronously) {
    return commandManager_->invokeDirectly(commandID, asynchronously);
  }

  virtual void operator()(CommandID id) {
    if (!invokeDirectly(id, false))
      LOG(DFATAL) << "Failed to invoke " << CommandIDEncoder::commandIDName(id);
  }

  virtual void operator()(bool d) { Lock l(lock_); disabled_ = d; }

  virtual bool perform(const InvocationInfo&);

  InvocationInfo lastInvocation() const;

  void addCallback(CommandID id,
                   Callback* cb,
                   const String& name,
                   const String& category,
                   const String& desc);

  ApplicationCommandManager* commandManager() { return commandManager_; }
  void addCommandItem(PopupMenu*,
                      CommandID,
                      bool enable,
                      const String& name,
                      int flags);
  CommandRecordTable* commandRecordTable() { return &table_; }
  ApplicationCommandTarget* target() { return target_.get(); }
  CommandRecord* find(CommandID);

 private:
  CommandRecordTable table_;

  CriticalSection lock_;
  InvocationInfo lastInvocation_;
  bool disabled_;

  ptr<CommandData> commandData_;
  ApplicationCommandManager* commandManager_;
  ptr<ApplicationCommandTarget> target_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(TargetManager);
};

}  // namespace rec
}  // namespace command

#endif  // __REC_SLOW_COMMANDTARGET__
