#include "rec/app/LanguageListener.h"
#include "rec/app/AppSettings.pb.h"
#include "rec/data/DataListener.h"

namespace rec {
namespace app {

class LanguageListener::Updater : public GlobalDataListener<AppSettings> {
 public:
  explicit Updater(LanguageListener* client) : client_(client) {}

  virtual void operator()(const AppSettings&) {
    client_->languageChanged();
  }

 private:
  LanguageListener* client_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Updater);
};

LanguageListener::LanguageListener() : updater_(new Updater(this)) {}
LanguageListener::~LanguageListener() {}

}  // namespace app
}  // namespace rec

