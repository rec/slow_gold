#ifndef __REC_SLOW_ADVANCEDMENUMAKER__
#define __REC_SLOW_ADVANCEDMENUMAKER__

#include "rec/slow/BasicMenuMaker.h"

namespace rec {
namespace slow {

class AdvancedMenuMaker : public BasicMenuMaker {
 public:
  AdvancedMenuMaker(Instance* i, const IsWholeSong& isWholeSong, bool empty)
      : BasicMenuMaker(i, isWholeSong, empty) {
  }
  virtual ~AdvancedMenuMaker() {}

  virtual const StringArray getMenuBarNames() const;

 protected:
  virtual void addEditMenu();
  virtual void addFileMenu();
  virtual void addSelectMenu();
  virtual void addTransportMenu();
  virtual void addDisplayMenu();
  virtual void addHelpMenu();
  virtual bool addMenu(const String& menuName);

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(AdvancedMenuMaker);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_ADVANCEDMENUMAKER__
