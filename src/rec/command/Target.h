#ifndef __REC_SLOW_COMMANDTARGET__
#define __REC_SLOW_COMMANDTARGET__

#include <map>

#include "rec/base/STL.h"

namespace rec {
namespace util {
namespace thread {

class Callback

}  // namespace thread
}  // namespace util

namespace command {

struct CommandCallback;

// An implementation of ApplicationCommandTarget that lets you register commands
// with a callback.
class Target : public ApplicationCommandTarget {
 public:
  Target();

  // ApplicationTarget virtual methods.
  virtual void getAllCommands(Array<CommandID>&);
  virtual void getCommandInfo(CommandID, ApplicationCommandInfo&);
  virtual bool perform(const InvocationInfo&); // { return false; }

  InvocationInfo lastInvocation() const;

  void add(thread::Callback* callback, const ApplicationCommandInfo& info);
  void add(CommandID id, thread::Callback* callback, const String& name,
           const String& category, const String& desc, int flags = 0);

 private:
  typedef std::hash_map<juce::CommandID, CommandCallback*> CommandMap;

  CriticalSection lock_;
  InvocationInfo lastInvocation_;

  CommandMap map_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Target);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_SLOW_COMMANDTARGET__
