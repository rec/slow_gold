#ifndef __REC_SLOW_ADVANCEDMENUMAKER__
#define __REC_SLOW_ADVANCEDMENUMAKER__

#include "rec/slow/MenuMaker.h"

namespace rec {
namespace slow {

class AdvancedMenuMaker : public MenuMaker {
 public:
  AdvancedMenuMaker(command::TargetManager* t) : MenuMaker(t) {}
  virtual ~AdvancedMenuMaker() {}

  virtual const StringArray getMenuBarNames() const;

 protected:
  void addAudioMenu();
  void addFileMenu();
  void addEditMenu();
  void addSelectMenu();
  void addTransportMenu();
  void addDisplayMenu();
  virtual void addMenu(const String& menuName);

 private:
  command::TargetManager* targetManager_;
  bool isAdvanced_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(AdvancedMenuMaker);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_ADVANCEDMENUMAKER__
