#ifndef __REC_APP_PROGRAM__
#define __REC_APP_PROGRAM__

// A class representing all the things a specific program needs to operate.

#include "rec/base/base.h"
#include "rec/gui/menu/Menu.pb.h"

namespace rec {

namespace app {

class Program {
 public:
  Program() {}
  virtual ~Program() = 0;

  virtual const gui::menu::MenuCollection& menus() const = 0;
  virtual uint32 menuBar() const = 0;
  virtual bool hasProperty(const string& name) const = 0;
  virtual gui::menu::MenuName makeName(const gui::menu::MenuEntry&, CommandID)
    const = 0;

  virtual ApplicationCommandTarget* applicationCommandTarget() const = 0;
};

}  // namespace app
}  // namespace rec


#endif  // __REC_APP_PROGRAM__
