#ifndef __REC_SLOW_MENUMAKER__
#define __REC_SLOW_MENUMAKER__

#include "rec/base/base.h"
#include "rec/command/CommandIDEncoder.h"

namespace rec {

namespace command { class TargetManager; }

namespace slow {

class MenuMaker {
 public:
  static const int SLOT_COUNT = 10;

  MenuMaker(command::TargetManager* t) : targetManager_(t) {}

  const PopupMenu makeMenu(const String& name);

 private:
  void add(CommandID id,
           const String& name = String::empty,
           bool enabled = true,
           PopupMenu* m = NULL);

  void addRepeat(command::Command::Type command,
                 int slot,
                 const String& name = String::empty,
                 bool enabled = true,
                 PopupMenu* m = NULL);

  void addMenu(const String& menuName);

  void addEnabled(command::Command::Type command, bool enabled);
  void addBank(command::Command::Type command, const String& name,
               int begin = command::CommandIDEncoder::FIRST,
               int end = SLOT_COUNT);

  void addAudioMenu();
  void addFileMenu();
  void addEditMenu();
  void addSelectMenu();
  void addTransportMenu();
  void addDisplayMenu();

 private:
  command::TargetManager* targetManager_;
  PopupMenu menu_;
  bool isAdvanced_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(MenuMaker);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_MENUMAKER__
