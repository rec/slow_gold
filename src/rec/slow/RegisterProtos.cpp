#include "rec/slow/RegisterProtos.h"

#include "rec/app/AppSettings.pb.h"
#include "rec/audio/AudioSettings.pb.h"
#include "rec/audio/source/Stereo.pb.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/util/Gain.pb.h"
#include "rec/base/Trans.pb.h"
#include "rec/command/Command.pb.h"
#include "rec/command/map/CommandMap.pb.h"
#include "rec/data/DataCenter.h"
#include "rec/gui/DialogFiles.pb.h"
#include "rec/gui/WindowPosition.pb.h"
#include "rec/gui/menu/RecentFiles.pb.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/util/LoopPoint.pb.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/SystemStats.pb.h"
#include "rec/util/proto/MessageRegistrar.h"
#include "rec/widget/tree/NavigatorConfig.pb.h"
#include "rec/widget/waveform/Viewport.pb.h"
#include "rec/widget/waveform/Waveform.pb.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace slow {

void registerProtos() {
  using namespace rec::data;
  MessageRegistrar* r = getDataCenter()->messageRegistrar();

  registerGlobal<app::AppSettings>(r);
  registerGlobal<audio::AudioSettings>(r);
  registerGlobal<command::CommandMapProto>(r);
  registerGlobal<command::Commands>(r);
  registerGlobal<command::KeyStrokeCommandMapProto>(r);
  registerGlobal<command::MidiCommandMapProto>(r);
  registerGlobal<gui::DialogFiles>(r);
  registerGlobal<gui::RecentFiles>(r);
  registerGlobal<gui::WindowPosition>(r);
  registerGlobal<slow::AppLayout>(r);
  registerGlobal<slow::GuiSettings>(r);
  registerGlobal<util::Mode>(r);
  registerGlobal<util::SystemStats>(r);
  registerGlobal<util::file::VirtualFile>(r);
  registerGlobal<util::file::VirtualFileList>(r);
  registerGlobal<widget::tree::NavigatorConfig>(r);
  registerGlobal<widget::waveform::WaveformProto>(r);

  registerLocal<audio::Gain>(r);
  registerLocal<audio::source::StereoProto>(r);
  registerLocal<audio::stretch::Stretch>(r);
  registerLocal<music::Metadata>(r);
  registerLocal<util::LoopPointList>(r);
  registerLocal<widget::waveform::Viewport>(r);
  registerLocal<widget::waveform::Zoom>(r);
}

}  // namespace slow
}  // namespace rec
