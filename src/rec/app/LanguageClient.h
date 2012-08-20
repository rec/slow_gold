#ifndef __REC_APP_LANGUAGECLIENT__
#define __REC_APP_LANGUAGECLIENT__

#include "rec/base/base.h"

namespace rec {
namespace app {

class LanguageClient {
 public:
  LanguageClient();
  virtual ~LanguageClient();

  virtual void languageChanged() = 0;

 private:
  class Updater;
  ptr<Updater> updater_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(LanguageClient);
};

}  // namespace app
}  // namespace rec

#endif  // __REC_APP_LANGUAGECLIENT__
