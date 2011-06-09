#ifndef __REC_COMMAND_MIDICOMMANDMAPEDITOR__
#define __REC_COMMAND_MIDICOMMANDMAPEDITOR__

#include "rec/command/CommandMapEditor.h"
#include "rec/command/CommandMapEditButton.h"
#include "rec/command/CommandMapEditorMappingItem.h"

namespace rec {
namespace command {

class MidiCommandMapEditor : public CommandMapEditor {
public:
    MidiCommandMapEditor(ApplicationCommandManager&,
                         MidiCommandMap&,
                         ChangeBroadcaster&);

    virtual void addButton(CommandMapEditButton* button);
    virtual void removeButton(CommandMapEditButton* button);
    virtual void addChildren(CommandMapItemComponent* comp);

    MidiCommandMap& getMappings() { return mappings; }

    static const int MAX_NUM_ASSIGNMENTS = 3;

private:
    MidiCommandMap& mappings;;
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_MIDICOMMANDMAPEDITOR__
