#include "rec/support/SupportWindow.h"

#include "rec/app/Files.h"
#include "rec/app/GenericApplication.h"
#include "rec/data/DataOps.h"
#include "rec/data/DataCenter.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/Geometry.h"
#include "rec/slow/Components.h"
#include "rec/slow/AboutWindow.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/slow/Instance.h"
#include "rec/slow/MainPage.h"
#include "rec/slow/Menus.h"
#include "rec/slow/RegisterProtos.h"
#include "rec/slow/TranslateAll.h"
#include "rec/slow/callbacks/GlobalCallbacks.h"
#include "rec/util/Defaulter.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/thread/MakeThread.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace slow {

using namespace juce;

SupportWindow::SupportWindow(app::GenericApplication* application)
    : app::Window(application, "SlowGold", Colours::azure,
                  DocumentWindow::allButtons, true),
      HasInstance(NULL) {
}

SupportWindow::~SupportWindow() {}

}  // namespace slow

namespace support {

using namespace rec::data;

void initialize(app::GenericApplication* app) {
  slow::requestSupport();
  app->quit();
}

void shutdown(app::GenericApplication*) {}

}  // namespace support
}  // namespace rec
