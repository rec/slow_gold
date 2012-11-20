#ifndef __REC_COMMAND_COMMANDMAPITEMCOMPONENT__
#define __REC_COMMAND_COMMANDMAPITEMCOMPONENT__

#include "rec/command/map/CommandMapEditor.h"

namespace rec {
namespace command {

class CommandMapItemComponent  : public Component {
 public:
  CommandMapItemComponent(CommandMapEditor&, CommandID);
  void addButton(const String& desc, const int index, const bool isReadOnly);
  void paint(Graphics&);
  void resized();

  const CommandID commandID_;

 private:
  CommandMapEditor& owner_;
  OwnedArray<CommandMapEditButton> buttons_;

  enum { maxNumAssignments = 3 };
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPITEMCOMPONENT__
