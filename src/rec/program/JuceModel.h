#ifndef __REC_APP_PROGRAM_INSTANCE__
#define __REC_APP_PROGRAM_INSTANCE__

#include <unordered_map>

#include "rec/base/base.h"

namespace rec {
namespace program {

class JuceModelImpl;
class Program;

class JuceModel : public ApplicationCommandTarget, public MenuBarModel {
 public:
  JuceModel(Program*);
  ~JuceModel();

  ApplicationCommandTarget* getNextCommandTarget() override { return NULL; }
  void getAllCommands(juce::Array<CommandID>& commands) override;
  void getCommandInfo(CommandID, ApplicationCommandInfo&) override;
  bool perform(const InvocationInfo& info) override;

  StringArray getMenuBarNames() override;
  PopupMenu getMenuForIndex(int menuIndex, const String& name) override;
  void menuItemSelected(int, int) override {}

  Program* program() { return program_; }
  ApplicationCommandManager* applicationCommandManager();

 private:
  unique_ptr<JuceModelImpl> impl_;
  Program* program_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(JuceModel);
};

}  // namespace program
}  // namespace rec


#endif  // __REC_APP_PROGRAM_INSTANCE__
