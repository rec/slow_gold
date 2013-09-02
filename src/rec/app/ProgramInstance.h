#ifndef __REC_APP_PROGRAM_INSTANCE__
#define __REC_APP_PROGRAM_INSTANCE__

#include <unordered_map>

#include "rec/base/base.h"
#include "rec/command/Command.pb.h"

namespace rec {
namespace app {

class Program;

class ProgramInstance : public juce::ApplicationCommandTarget {
 public:
  ProgramInstance(Program*);
  ~ProgramInstance() {}

  juce::ApplicationCommandTarget* getNextCommandTarget() override { return NULL; }
  void getAllCommands(juce::Array<CommandID>& commands) override;
  void getCommandInfo(CommandID, ApplicationCommandInfo&) override;
  bool perform(const InvocationInfo& info) override;

  typedef std::unordered_map<CommandID, command::Command> ProgramMap;

 private:
  Program* program_;
  ProgramMap programMap_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(ProgramInstance);
};

}  // namespace app
}  // namespace rec


#endif  // __REC_APP_PROGRAM_INSTANCE__
