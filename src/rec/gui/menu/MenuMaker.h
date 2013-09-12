#ifndef __REC_SLOW_MENUMAKER__
#define __REC_SLOW_MENUMAKER__

#include "rec/base/base.h"
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

  void addEnabled(CommandID, Enable);
  void addEnabled(CommandID t, bool enable) {
    addEnabled(t, enable ? ENABLE : DISABLE);
  }

  void addRepeat(CommandID,
                 int slot,
                 const String& name = String::empty,
                 PopupMenu* m = nullptr,
                 int flags = -1);

 protected:
  static const int DEFAULT_FLAGS = -1;

  void addBasic(CommandID id);

  void addSimpleRepeat(CommandID, int slot, PopupMenu*);

  virtual bool addMenu(const String& menuName) = 0;

  void addEnabledName(CommandID, Enable, const String& name);
  void addEnabledName(CommandID t, bool en, const String& name) {
    addEnabledName(t, en ? ENABLE : DISABLE, name);
  }
  void addBank(CommandID, const String& name);

  PopupMenu menu_;
  const IsWholeSong& isWholeSong_;
  const bool empty_;

 private:
  void addFull(CommandID id,
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
