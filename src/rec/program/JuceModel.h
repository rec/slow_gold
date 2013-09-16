#ifndef __REC_APP_PROGRAM_INSTANCE__
#define __REC_APP_PROGRAM_INSTANCE__

#include <unordered_map>

#include "rec/util/Listener.h"

namespace rec {
namespace program {

class JuceModelImpl;
class Program;

class JuceModel : public ApplicationCommandTarget,
                  public MenuBarModel,
                  public Listener<Enable> {
 public:
  JuceModel(Program* p);
  void init();

  ~JuceModel();

  ApplicationCommandTarget* getNextCommandTarget() override { return NULL; }
  void getAllCommands(juce::Array<CommandID>& commands) override;
  void getCommandInfo(CommandID, ApplicationCommandInfo&) override;
  bool perform(const InvocationInfo& info) override;

  StringArray getMenuBarNames() override;
  PopupMenu getMenuForIndex(int menuIndex, const String& name) override;
  void menuItemSelected(int, int) override {}

  Program* program() { return program_; }

  void invokeAndCheck(CommandID);
  void operator()(Enable) override;

  ApplicationCommandManager* applicationCommandManager() {
    return &applicationCommandManager_;
  }

  void startThreads();
  void stopThreads();
  Thread* getThread(const string&);

 private:
  unique_ptr<JuceModelImpl> impl_;
  Program* program_;
  ApplicationCommandManager applicationCommandManager_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(JuceModel);
};

JuceModel* juceModel();

inline void menuItemsChanged() {
  juceModel()->menuItemsChanged();
}

inline ApplicationCommandManager* applicationCommandManager() {
  return juceModel()->applicationCommandManager();
}

}  // namespace program
}  // namespace rec

#endif  // __REC_APP_PROGRAM_INSTANCE__
