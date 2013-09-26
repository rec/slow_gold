#ifndef __REC_APP_PROGRAM_INSTANCE__
#define __REC_APP_PROGRAM_INSTANCE__

#include <unordered_map>

#include "rec/util/Listener.h"

namespace rec { namespace command { class CommandMapProto; }}
namespace rec { namespace gui { class Constants; }}
namespace rec { namespace gui { class Layout; }}

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

  ApplicationCommandTarget* getNextCommandTarget() override { return nullptr; }
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

  // @throws std::out_of_range
  const gui::Layout& getLayout(const string&) const;
  const gui::Constants& constants() const;

  void startThreads();
  void stopThreads();
  Thread* getThread(const string&);

  const command::CommandMapProto& keyMap() const;

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
