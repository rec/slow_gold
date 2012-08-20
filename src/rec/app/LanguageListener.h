#ifndef __REC_APP_LANGUAGELISTENER__
#define __REC_APP_LANGUAGELISTENER__

#include "rec/base/base.h"

namespace rec {
namespace app {

class LanguageListener {
 public:
  LanguageListener();
  virtual ~LanguageListener();

  virtual void languageChanged() = 0;

 private:
  class Updater;
  ptr<Updater> updater_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(LanguageListener);
};

}  // namespace app
}  // namespace rec

#endif  // __REC_APP_LANGUAGELISTENER__
