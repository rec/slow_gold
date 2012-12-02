#ifndef __REC_COMMAND_MIDICOMMANDMAPEDITOR__
#define __REC_COMMAND_MIDICOMMANDMAPEDITOR__

#include "rec/command/map/Editor.h"
#include "rec/command/map/MidiCommandMap.h"
#include "rec/command/map/Key.h"
#include "rec/util/Listener.h"

namespace rec {
namespace command {

class MidiEditor : public Editor,
                             public Listener<const MidiMessage&> {
 public:
  MidiEditor(ApplicationCommandManager* acm, MidiCommandMap* mcm)
      : Editor(acm, mcm), mappings_(mcm), isListening_(false) {
  }

  virtual const String name() const;
  virtual bool isValid(const string&) const { return true; }
  virtual const String getDescription(const string&) const;
  virtual void operator()(const MidiMessage& msg) {
  virtual EntryWindow* newWindow();

 private:
  MidiCommandMap* mappings_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(MidiEditor);
};

}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_MIDICOMMANDMAPEDITOR__
