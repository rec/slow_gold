#ifndef __REC_SLOW_MENUMAKER__
#define __REC_SLOW_MENUMAKER__

#include "rec/base/base.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/slow/IsWholeSong.h"
#include "rec/util/thread/Callback.h"

namespace rec {

namespace command { class TargetManager; }

namespace slow {

class MenuMaker {
 public:
  static const int SLOT_COUNT = 10;

  MenuMaker(command::TargetManager* t,
            const IsWholeSong& isWholeSong,
            bool isEmpty)
      : isWholeSong_(isWholeSong), isEmpty_(isEmpty), targetManager_(t) {
  }
  virtual ~MenuMaker() {}

  const PopupMenu makeMenu(const String& name);
  virtual const StringArray getMenuBarNames() const = 0;

 protected:
  void add(CommandID id,
           const String& name = String::empty,
           bool enabled = true,
           PopupMenu* m = NULL,
           int flags = 0);

  void addRepeat(command::Command::Type command,
                 int slot,
                 const String& name = String::empty,
                 bool enabled = true,
                 PopupMenu* m = NULL,
                 int flags = 0);

  virtual bool addMenu(const String& menuName) = 0;

  void addEnabled(command::Command::Type command, bool enabled);
  void addBank(command::Command::Type command, const String& name,
               int begin = command::CommandIDEncoder::FIRST,
               int end = SLOT_COUNT);

  PopupMenu menu_;
  const IsWholeSong& isWholeSong_;
  const bool isEmpty_;

 private:
  command::TargetManager* targetManager_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(MenuMaker);
};

MenuMaker* makeMenuMaker(command::TargetManager* tm, bool isAdvanced,
                         const IsWholeSong&, bool isEmpty);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_MENUMAKER__
