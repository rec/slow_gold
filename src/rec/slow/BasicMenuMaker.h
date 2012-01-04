#ifndef __REC_SLOW_BASICMENUMAKER__
#define __REC_SLOW_BASICMENUMAKER__

#include "rec/slow/MenuMaker.h"

namespace rec {
namespace slow {

class BasicMenuMaker : public MenuMaker {
 public:
  BasicMenuMaker(command::TargetManager* t) : MenuMaker(t) {}
  virtual ~BasicMenuMaker() {}

  virtual const StringArray getMenuBarNames() const;

 protected:
  void addAudioMenu();
  void addFileMenu();
  void addEditMenu();
  void addSelectMenu();
  void addTransportMenu();
  virtual void addMenu(const String& menuName);

 private:
  command::TargetManager* targetManager_;
  bool isAdvanced_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(BasicMenuMaker);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_BASICMENUMAKER__
