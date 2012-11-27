#ifndef __REC_SLOW_BASICMENUMAKER__
#define __REC_SLOW_BASICMENUMAKER__

#include "rec/slow/MenuMaker.h"
#include "rec/slow/IsWholeSong.h"

namespace rec {
namespace slow {

class BasicMenuMaker : public MenuMaker {
 public:
  BasicMenuMaker(slow::Instance* i, const IsWholeSong& isWholeSong, bool empty)
      : MenuMaker(i, isWholeSong, empty) {
  }
  virtual ~BasicMenuMaker() {}

  virtual const StringArray getMenuBarNames() const;

 protected:
  virtual void addAudioMenu();
  virtual void addFileMenu();
  virtual void addEditMenu();
  virtual void addSelectMenu();
  virtual void addTransportMenu();
  virtual void addHelpMenu();

  virtual bool addMenu(const String& menuName);

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(BasicMenuMaker);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_BASICMENUMAKER__
