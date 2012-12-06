#ifndef __REC_COMMAND_KEYCOMMANDMAPEDITOR__
#define __REC_COMMAND_KEYCOMMANDMAPEDITOR__

#include "rec/command/map/Editor.h"

namespace rec {
namespace command {

class KeyStrokeEditor : public Editor, public juce::KeyListener {
 public:
  KeyStrokeEditor(ApplicationCommandManager* acm, CommandMap* mcm)
      : Editor(acm, mcm), mappings_(mcm) {
  }

  virtual const String name() const;
  virtual bool isValid(const string&) const;
  virtual const String getDescription(const string&) const;
  virtual bool keyPressed(const KeyPress&);
  virtual String getWindowTitle() const;
  virtual juce::AlertWindow* newWindow();

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(KeyStrokeEditor);
};


}  // namespace command
}  // namespace rec

#endif  // __REC_COMMAND_KEYCOMMANDMAPEDITOR__
