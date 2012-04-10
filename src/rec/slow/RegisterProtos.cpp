#include "rec/slow/RegisterProtos.h"

#include "rec/audio/source/Stereo.pb.h"
#include "rec/audio/stretch/Stretch.pb.h"
#include "rec/audio/util/Gain.pb.h"
#include "rec/command/Command.pb.h"
#include "rec/command/map/CommandMap.pb.h"
#include "rec/data/MessageRegistrar.h"
#include "rec/data/MessageRegistrarAndMaker.h"
#include "rec/data/DataCenter.h"
#include "rec/gui/RecentFiles.pb.h"
#include "rec/gui/WindowPosition.pb.h"
#include "rec/slow/AppLayout.pb.h"
#include "rec/slow/GuiSettings.pb.h"
#include "rec/util/LoopPoint.pb.h"
#include "rec/util/Mode.pb.h"
#include "rec/util/SystemStats.pb.h"
#include "rec/widget/tree/NavigatorConfig.pb.h"
#include "rec/widget/waveform/Waveform.pb.h"
#include "rec/widget/waveform/Zoom.pb.h"

namespace rec {
namespace slow {

void registerProtos() {
  using namespace rec::data;
  MessageRegistrar* r = getDataCenter().registry_.get();

  registerClass<audio::Gain>(r);
  registerClass<audio::source::StereoProto>(r);
  registerClass<audio::stretch::Stretch>(r);
  registerClass<command::CommandMapProto>(r);
  registerClass<command::Commands>(r);
  registerClass<gui::RecentFiles>(r);
  registerClass<gui::WindowPosition>(r);
  registerClass<music::Metadata>(r);
  registerClass<slow::AppLayout>(r);
  registerClass<slow::GuiSettings>(r);
  registerClass<util::LoopPointList>(r);
  registerClass<util::Mode>(r);
  registerClass<util::SystemStats>(r);
  registerClass<util::file::VirtualFile>(r);
  registerClass<util::file::VirtualFileList>(r);
  registerClass<widget::tree::NavigatorConfig>(r);
  registerClass<widget::waveform::WaveformProto>(r);
  registerClass<widget::waveform::ZoomProto>(r);
}

}  // namespace slow
}  // namespace rec
