#ifndef __REC_SLOW_MENUITEM__
#define __REC_SLOW_MENUITEM__

#include "rec/base/base.h"

namespace rec {

namespace command { class CommandRecordTable; }

namespace slow {

struct MenuItem {
  static const int DEFAULT_FLAGS = -1;

  MenuItem() : flags_(DEFAULT_FLAGS), enable_(ENABLED) {}
  MenuItem(CommandID id, const String& name) : id_(id), name_(name) {}

  void add(PopupMenu*, command::CommandRecordTable*,
           ApplicationCommandManager*);

  CommandID id_;
  String name_;
  int flags_;
  Enable enable_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(MenuItem);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_MENUITEM__
