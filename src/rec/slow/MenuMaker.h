#ifndef __REC_SLOW_MENUMAKER__
#define __REC_SLOW_MENUMAKER__

#include "rec/base/base.h"
#include "rec/command/ID.h"
#include "rec/slow/IsWholeSong.h"
#include "rec/slow/HasInstance.h"
#include "rec/util/thread/Callback.h"

namespace rec {

namespace command { class CommandRecordTable; }

namespace slow {

class Instance;

class MenuMaker : public HasInstance {
 public:
  static const int SLOT_COUNT = 10;

  MenuMaker(Instance* i,
            const IsWholeSong& isWholeSong,
            bool empty)
      : HasInstance(i), isWholeSong_(isWholeSong), empty_(empty) {
  }
  virtual ~MenuMaker() {}

  const PopupMenu makeMenu(const String& name);
  virtual const StringArray getMenuBarNames() const = 0;
  bool empty() const { return empty_; }
  PopupMenu* menu() { return &menu_; }

  void addSeparator() { menu_.addSeparator(); }

  void addEnabled(command::Command::Type, Enable);
  void addEnabled(command::Command::Type t, bool enable) {
    addEnabled(t, enable ? ENABLE : DISABLE);
  }

  void addRepeat(command::Command::Type,
                 int slot,
                 const String& name = String::empty,
                 PopupMenu* m = NULL,
                 int flags = -1);

 protected:
  static const int DEFAULT_FLAGS = -1;

  void addBasic(command::ID id);

  void addSimpleRepeat(command::Command::Type, int slot, PopupMenu*);

  virtual bool addMenu(const String& menuName) = 0;

  void addEnabledName(command::Command::Type, Enable, const String& name);
  void addEnabledName(command::Command::Type t, bool en, const String& name) {
    addEnabledName(t, en ? ENABLE : DISABLE, name);
  }
  void addBank(command::Command::Type, const String& name);

  PopupMenu menu_;
  const IsWholeSong& isWholeSong_;
  const bool empty_;

 private:
  void addFull(command::ID id,
               const String& name,
               Enable,
               PopupMenu* m,
               int flags);

  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(MenuMaker);
};

MenuMaker* makeMenuMaker(Instance*, bool isAdvanced,
                         const IsWholeSong&, bool empty);

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_MENUMAKER__
