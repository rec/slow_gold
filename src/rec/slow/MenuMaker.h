#ifndef __REC_SLOW_MENUMAKER__
#define __REC_SLOW_MENUMAKER__

#include "rec/base/base.h"
#include "rec/command/CommandIDEncoder.h"
#include "rec/slow/IsWholeSong.h"
#include "rec/util/thread/Callback.h"

namespace rec {

namespace slow {

class Target;

class MenuMaker {
 public:
  static const int SLOT_COUNT = 10;

  MenuMaker(Target* t, const IsWholeSong& isWholeSong, bool empty)
      : isWholeSong_(isWholeSong), empty_(empty), target_(t) {
  }
  virtual ~MenuMaker() {}

  const PopupMenu makeMenu(const String& name);
  virtual const StringArray getMenuBarNames() const = 0;
  bool empty() const { return empty_; }
  PopupMenu* menu() { return &menu_; }

  void addSeparator() { menu_.addSeparator(); }

  void addEnabled(command::Command::Type, bool enable);
  void addRepeat(command::Command::Type,
                 int slot,
                 const String& name = String::empty,
                 PopupMenu* m = NULL,
                 int flags = -1);

 protected:
  static const int DEFAULT_FLAGS = -1;

  void addBasic(CommandID id);

  void addSimpleRepeat(command::Command::Type, int slot, PopupMenu*);

  virtual bool addMenu(const String& menuName) = 0;

  void addEnabledName(command::Command::Type, bool enable, const String& name);
  void addBank(command::Command::Type, const String& name);

  PopupMenu menu_;
  const IsWholeSong& isWholeSong_;
  const bool empty_;

 private:
  void addFull(CommandID id,
               const String& name,
               bool enabled,
               PopupMenu* m,
               int flags);

  Target* target_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(MenuMaker);
};

MenuMaker* makeMenuMaker(Target* tm, bool isAdvanced,
                         const IsWholeSong&, bool empty);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_MENUMAKER__
