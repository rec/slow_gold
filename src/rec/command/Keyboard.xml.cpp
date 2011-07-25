#include "rec/command/Keyboard.xml.h"

#include "rec/base/ArraySize.h"
#include "rec/data/Binary.h"

namespace rec {
namespace command {

juce::XmlElement* Keyboard::create() {
  static const char data[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
  "\n"
  "<KEYMAPPINGS basedOnDefaults=\"0\">\n"
  "  <MAPPING commandId=\"1001\" description=\"Quits the application\" key=\"command + Q\"/>\n"
  "  <MAPPING commandId=\"1\" description=\"Add a loop point at the current time.\"\n"
  "           key=\"command + =\"/>\n"
  "  <MAPPING commandId=\"1\" description=\"Add a loop point at the current time.\"\n"
  "           key=\"numpad +\"/>\n"
  "  <MAPPING commandId=\"1e\" description=\"Select loop 1 and unselect all other loops.\"\n"
  "           key=\"command + 1\"/>\n"
  "  <MAPPING commandId=\"1f\" description=\"Select loop 2 and unselect all other loops.\"\n"
  "           key=\"command + 2\"/>\n"
  "  <MAPPING commandId=\"20\" description=\"Select loop 3 and unselect all other loops.\"\n"
  "           key=\"command + 3\"/>\n"
  "  <MAPPING commandId=\"21\" description=\"Select loop 4 and unselect all other loops.\"\n"
  "           key=\"command + 4\"/>\n"
  "  <MAPPING commandId=\"22\" description=\"Select loop 5 and unselect all other loops.\"\n"
  "           key=\"command + 5\"/>\n"
  "  <MAPPING commandId=\"23\" description=\"Select loop 6 and unselect all other loops.\"\n"
  "           key=\"command + 6\"/>\n"
  "  <MAPPING commandId=\"24\" description=\"Select loop 7 and unselect all other loops.\"\n"
  "           key=\"command + 7\"/>\n"
  "  <MAPPING commandId=\"25\" description=\"Select loop 8 and unselect all other loops.\"\n"
  "           key=\"command + 8\"/>\n"
  "  <MAPPING commandId=\"26\" description=\"Select loop 9 and unselect all other loops.\"\n"
  "           key=\"command + 9\"/>\n"
  "  <MAPPING commandId=\"27\" description=\"Select loop 10 and unselect all other loops.\"\n"
  "           key=\"command + 0\"/>\n"
  "  <MAPPING commandId=\"2\" description=\"Open the Audio Preferences pane.\"\n"
  "           key=\"command + ;\"/>\n"
  "  <MAPPING commandId=\"8\" description=\"Immediately jump to the previous segment and select it.\"\n"
  "           key=\"cursor right\"/>\n"
  "  <MAPPING commandId=\"9\" description=\"Immediately jump to the next loop point and select it.\"\n"
  "           key=\"cursor left\"/>\n"
  "  <MAPPING commandId=\"32\" description=\"Start or pause\" key=\"spacebar\"/>\n"
  "  <MAPPING commandId=\"32\" description=\"Start or pause\" key=\"command + spacebar\"/>\n"
  "  <MAPPING commandId=\"13\" description=\"Unselect everything selected and vice-versa.\"\n"
  "           key=\"command + I\"/>\n"
  "  <MAPPING commandId=\"28\" description=\"Toggle loop 1 between selected and unselected\"\n"
  "           key=\"1\"/>\n"
  "  <MAPPING commandId=\"29\" description=\"Toggle loop 2 between selected and unselected\"\n"
  "           key=\"2\"/>\n"
  "  <MAPPING commandId=\"2a\" description=\"Toggle loop 3 between selected and unselected\"\n"
  "           key=\"3\"/>\n"
  "  <MAPPING commandId=\"2b\" description=\"Toggle loop 4 between selected and unselected\"\n"
  "           key=\"4\"/>\n"
  "  <MAPPING commandId=\"2c\" description=\"Toggle loop 5 between selected and unselected\"\n"
  "           key=\"5\"/>\n"
  "  <MAPPING commandId=\"2d\" description=\"Toggle loop 6 between selected and unselected\"\n"
  "           key=\"6\"/>\n"
  "  <MAPPING commandId=\"2e\" description=\"Toggle loop 7 between selected and unselected\"\n"
  "           key=\"7\"/>\n"
  "  <MAPPING commandId=\"2f\" description=\"Toggle loop 8 between selected and unselected\"\n"
  "           key=\"8\"/>\n"
  "  <MAPPING commandId=\"30\" description=\"Toggle loop 9 between selected and unselected\"\n"
  "           key=\"9\"/>\n"
  "  <MAPPING commandId=\"31\" description=\"Toggle loop 10 between selected and unselected\"\n"
  "           key=\"0\"/>\n"
  "  <MAPPING commandId=\"3c\" description=\"Unselect loop 1 only\" key=\"option + 1\"/>\n"
  "  <MAPPING commandId=\"3d\" description=\"Unselect loop 2 only\" key=\"option + 2\"/>\n"
  "  <MAPPING commandId=\"3e\" description=\"Unselect loop 3 only\" key=\"option + 3\"/>\n"
  "  <MAPPING commandId=\"3f\" description=\"Unselect loop 4 only\" key=\"option + 4\"/>\n"
  "  <MAPPING commandId=\"40\" description=\"Unselect loop 5 only\" key=\"option + 5\"/>\n"
  "  <MAPPING commandId=\"41\" description=\"Unselect loop 6 only\" key=\"option + 6\"/>\n"
  "  <MAPPING commandId=\"42\" description=\"Unselect loop 7 only\" key=\"option + 7\"/>\n"
  "  <MAPPING commandId=\"43\" description=\"Unselect loop 8 only\" key=\"option + 8\"/>\n"
  "  <MAPPING commandId=\"44\" description=\"Unselect loop 9 only\" key=\"option + 9\"/>\n"
  "  <MAPPING commandId=\"45\" description=\"Unselect loop 10 only\" key=\"option + 0\"/>\n"
  "  <MAPPING commandId=\"1002\" description=\"Delete the current selection without changing the clipboard.\"\n"
  "           key=\"backspace\"/>\n"
  "  <MAPPING commandId=\"1003\" description=\"Copy the current selection to the clipboard and clear the selection.\"\n"
  "           key=\"command + x\"/>\n"
  "  <MAPPING commandId=\"1004\" description=\"Copy the current selection to the clipboard.\"\n"
  "           key=\"command + c\"/>\n"
  "  <MAPPING commandId=\"1005\" description=\"Replace the current selection with a copy of the clipboard.\"\n"
  "           key=\"command + v\"/>\n"
  "  <MAPPING commandId=\"6\" description=\"Close the current file\" key=\"command + W\"/>\n"
  "  <MAPPING commandId=\"7\" description=\"Eject all CDs and DVDs\" key=\"command + E\"/>\n"
  "  <MAPPING commandId=\"f\" description=\"Open a dialog to select a new audio file for looping.\"\n"
  "           key=\"command + o\"/>\n"
  "  <MAPPING commandId=\"11\" description=\"Edit midi mappings for commands.\"\n"
  "           key=\"command + M\"/>\n"
  "  <MAPPING commandId=\"12\" description=\"Edit keyboard mappings for commands.\"\n"
  "           key=\"command + K\"/>\n"
  "  <MAPPING commandId=\"1006\" description=\"Select all of the file\" key=\"command + A\"/>\n"
  "  <MAPPING commandId=\"1007\" description=\"Select none of the file\" key=\"command + D\"/>\n"
  "  <MAPPING commandId=\"3b\" description=\"Nudge gain down by 1dB\" key=\"cursor down\"/>\n"
  "  <MAPPING commandId=\"48\" description=\"Nudge gain up by 1dB\" key=\"cursor up\"/>\n"
  "  <MAPPING commandId=\"4d\" description=\"Toggle audio dim on and off.\" key=\"numpad .\"/>\n"
  "  <MAPPING commandId=\"4e\" description=\"Toggle audio mute on and off.\" key=\"numpad 0\"/>\n"
  "  <MAPPING commandId=\"4f\" description=\"Reset audio level to 0 dB\" key=\"numpad 1\"/>\n"
  "  <MAPPING commandId=\"14\" description=\"Select loop 1.\" key=\"shift + !\"/>\n"
  "  <MAPPING commandId=\"15\" description=\"Select loop 2.\" key=\"shift + @\"/>\n"
  "  <MAPPING commandId=\"16\" description=\"Select loop 3.\" key=\"shift + #\"/>\n"
  "  <MAPPING commandId=\"17\" description=\"Select loop 4.\" key=\"shift + $\"/>\n"
  "  <MAPPING commandId=\"18\" description=\"Select loop 5.\" key=\"shift + %\"/>\n"
  "  <MAPPING commandId=\"19\" description=\"Select loop 6.\" key=\"shift + &#94;\"/>\n"
  "  <MAPPING commandId=\"1a\" description=\"Select loop 7.\" key=\"shift + &amp;\"/>\n"
  "  <MAPPING commandId=\"1b\" description=\"Select loop 8.\" key=\"shift + *\"/>\n"
  "  <MAPPING commandId=\"1c\" description=\"Select loop 9.\" key=\"shift + (\"/>\n"
  "  <MAPPING commandId=\"1d\" description=\"Select loop 10.\" key=\"shift + )\"/>\n"
  "  <MAPPING commandId=\"3a\" description=\"Toggle selection between the current segment and the whole song.\"\n"
  "           key=\"return\"/>\n"
  "  <MAPPING commandId=\"3a\" description=\"Toggle selection between the current segment and the whole song.\"\n"
  "           key=\"command + return\"/>\n"
  "</KEYMAPPINGS>\n"
  "\n"
;
  return data::create<juce::XmlElement>(data, arraysize(data));
};

}  // namespace command
}  // namespace rec