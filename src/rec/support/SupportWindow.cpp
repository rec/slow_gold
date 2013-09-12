#include "rec/support/SupportWindow.h"

#include "rec/app/Files.h"
#include "rec/app/GenericApplication.h"
#include "rec/slow/callbacks/GlobalCallbacks.h"
#include "rec/support/RequestSupport.h"

namespace rec {
namespace slow {

using namespace juce;

SupportWindow::SupportWindow(app::GenericApplication* application)
    : app::Window(application, "SupportRequest", Colours::azure,
                  DocumentWindow::allButtons, true) {
}

}  // namespace slow

namespace support {

using namespace rec::data;

void initialize(app::GenericApplication* app) {
  requestSupport();
  app->quit();
}

void shutdown(app::GenericApplication*) {}

}  // namespace support
}  // namespace rec
