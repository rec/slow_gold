#pragma once

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
    std::unique_ptr<Updater> updater_;

    DISALLOW_COPY_ASSIGN_AND_LEAKS(LanguageListener);
};

}  // namespace app
}  // namespace rec
