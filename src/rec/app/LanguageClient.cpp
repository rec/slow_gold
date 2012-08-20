#include "rec/app/LanguageClient.h"
#include "rec/app/AppSettings.pb.h"
#include "rec/data/DataListener.h"

namespace rec {
namespace app {

class LanguageClient::Updater : public GlobalDataListener<AppSettings> {
 public:
  explicit Updater(LanguageClient* client) : client_(client) {}

  virtual void operator()(const AppSettings&) {
    client_->languageChanged();
  }

 private:
  LanguageClient* client_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Updater);
};

LanguageClient::LanguageClient() : updater_(new Updater(this)) {}
LanguageClient::~LanguageClient() {}

}  // namespace app
}  // namespace rec
