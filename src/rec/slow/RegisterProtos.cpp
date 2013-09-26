#include "rec/slow/RegisterProtos.h"

#include "rec/app/AppSettings.pb.h"
#include "rec/audio/AudioSettings.pb.h"
#include "rec/audio/PlayState.pb.h"
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

  registerProto<app::AppSettings>(r);
  registerProto<audio::AudioSettings>(r);
  registerProto<audio::PlayState>(r);
  registerProto<command::CommandMapProto>(r);
  registerProto<command::Commands>(r);
  registerProto<command::KeyStrokeCommandMapProto>(r);
  registerProto<command::MidiCommandMapProto>(r);
  registerProto<gui::DialogFiles>(r);
  registerProto<gui::RecentFiles>(r);
  registerProto<gui::WindowPosition>(r);
  registerProto<slow::AppLayout>(r);
  registerProto<slow::GuiSettings>(r);
  registerProto<util::Mode>(r);
  registerProto<util::SystemStats>(r);
  registerProto<util::file::VirtualFile>(r);
  registerProto<util::file::VirtualFileList>(r);
  registerProto<widget::tree::NavigatorConfig>(r);
  registerProto<widget::waveform::WaveformProto>(r);

  registerFileProto<audio::Gain>(r);
  registerFileProto<audio::source::StereoProto>(r);
  registerFileProto<audio::stretch::Stretch>(r);
  registerFileProto<music::Metadata>(r);
  registerFileProto<util::LoopPointList>(r);
  registerFileProto<widget::waveform::Viewport>(r);
  registerFileProto<widget::waveform::Zoom>(r);
}

}  // namespace slow
}  // namespace rec
