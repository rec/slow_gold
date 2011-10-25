#include "rec/slow/Listeners.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/data/Data.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/DropFiles.h"
#include "rec/util/LoopPoint.h"
#include "rec/slow/Components.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Model.h"
#include "rec/slow/MouseListener.h"
#include "rec/slow/Target.h"
#include "rec/slow/Threads.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/thread/MakeCallback.h"

#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace slow {

using namespace rec::audio::source;
using namespace rec::audio::stretch;
using namespace rec::audio::util;
using namespace rec::gui::audio;
using namespace rec::widget::tree;
using namespace rec::widget::waveform;

Listeners::Listeners(Instance* i) : HasInstance(i) {
}

Listeners::~Listeners() {}


#ifdef TODO

void MainPage::loadRecentFile(int menuItemId) {
  gui::RecentFiles recent = gui::getSortedRecentFiles();
  const VirtualFile& file = recent.file(menuItemId).file();
  data::set(file);
}

static const int BLOCKSIZE = 1024;
static const int SAMPLE_RATE = 44100;

void PlaybackController::operator()(RealTime time) {
  enableLoopPointButton(loops_.isNewLoopPoint(time));  // TODO
}

void PlaybackController::enableLoopPointButton(bool e) {
  if (e != transportController_.getLoopPointButtonEnabled()) {
    thread::callAsync(&transportController_,
                      &gui::TransportController::enableLoopPointButton,
                      e);
  }
}

#endif

}  // namespace slow
}  // namespace rec

