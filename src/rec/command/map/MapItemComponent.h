#ifndef __REC_COMMAND_COMMANDMAPITEMCOMPONENT__
#define __REC_COMMAND_COMMANDMAPITEMCOMPONENT__

#include "rec/command/map/Editor.h"

namespace rec {
namespace command {

class MapItemComponent  : public Component {
 public:
  MapItemComponent(Editor*, CommandID);
  void addButton(const String& desc, const int index, const bool isReadOnly);
  void paint(Graphics&);
  void resized();

  const CommandID commandID_;

 private:
  Editor* const owner_;
  OwnedArray<EditButton> buttons_;

  enum { maxNumAssignments = 3 };
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_COMMANDMAPITEMCOMPONENT__
