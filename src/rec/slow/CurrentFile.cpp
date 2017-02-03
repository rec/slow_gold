#include "rec/slow/CurrentFile.h"

#include "rec/audio/PlayState.pb.h"
#include "rec/audio/AudioSettings.pb.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/util/BufferFiller.h"
#include "rec/audio/util/BufferedReader.h"
#include "rec/data/DataOps.h"
#include "rec/data/Opener.h"
#include "rec/music/CreateMusicFileReader.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/Instance.h"
#include "rec/slow/SlowWindow.h"
#include "rec/util/Loading.h"
#include "rec/util/StateListener.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/waveform/Viewport.pb.h"
#include "rec/widget/waveform/Waveform.h"

using namespace rec::widget::waveform;
using namespace rec::audio;

TRAN(RAN_OUT_OF_MEMORY, "Ran Out Of Memory For Your File");
TRAN(RAN_OUT_OF_MEMORY_FULL, "Sorry, there wasn't enough memory for the file.");

namespace rec {
namespace slow {

std::unique_ptr<Message> CurrentFile::getFileDescription() {
  return std::unique_ptr<Message>(data::getData<music::Metadata>(file_)->clone());
}

void CurrentFile::suspend() {
  saveState();
  getInstance()->reset();  // Stops the loading thread.
}

void CurrentFile::saveState() {
  if (not empty()) {
    auto& player = getInstance()->player_;
    PlayState state;
    state.set_time(player->getTime());
    state.set_is_playing(data::getProto<AudioSettings>().autoplay() and
                         player->state());
    data::setProto(state, file());
  }
}

void CurrentFile::resume() {
  if (not empty()) {
    getInstance()->fillerThread_->startThread();
    PlayState state = data::getProto<PlayState>(file());

    auto& currentTime = getInstance()->currentTime_;
    currentTime->jumpToTime(state.time());
  }
}

void CurrentFile::beforeFileChange() {
  MessageManagerLock l;
  broadcastState<Loading>(LOADING);
}

void CurrentFile::afterFileChange(const VirtualFile& newFile) {
  MessageManagerLock l;
  auto& components = getInstance()->components_;

  if (not empty())
    components->directoryTree()->refreshNode(file_);

  if (newFile.path_size())
    components->directoryTree()->refreshNode(newFile);

  broadcastState<Loading>(NOT_LOADING);
}

bool CurrentFile::determineIfFileEmpty(bool showError) {
  if (!file_.path_size()) {
    length_ = 0;
    return true;
  }

  music::MusicFileReader reader(file_);
  if (!reader.empty()) {
    getInstance()->bufferFiller_->setReader(file_, reader.release());
    length_ = getInstance()->bufferFiller_->length();
    if (length_)
      return false;
    reader.setError(t_RAN_OUT_OF_MEMORY, t_RAN_OUT_OF_MEMORY_FULL);
  }

  juce::LookAndFeel::getDefaultLookAndFeel().setUsingNativeAlertWindows(true);

  if (showError) {
    juce::AlertWindow::showMessageBox(juce::AlertWindow::WarningIcon,
                                      reader.errorTitle(),
                                      reader.errorDetails());
  }

  file_.Clear();
  return true;
}

void CurrentFile::nonEmptyFileLoaded() {
  Viewport viewport = data::getProto<Viewport>(file_);

  if (!viewport.has_zoom()) {
    Zoom* zoom = viewport.mutable_zoom();
    *zoom = data::getProto<Zoom>(file_);  // Legacy files.
    if (!zoom->has_begin())
      zoom->set_begin(0);
    if (!zoom->has_end())
      zoom->set_end(length_);
  }

  if (!viewport.has_loop_points()) {
    LoopPointList* loops = viewport.mutable_loop_points();
    *loops = data::getProto<LoopPointList>(file_);  // Legacy files.
    if (!loops->loop_point_size())
      loops->add_loop_point()->set_selected(true);
  }

  viewport.mutable_loop_points()->set_length(length_);
  viewport.mutable_loop_points()->set_sample_rate(getInstance()->bufferFiller_->reader()->
                                                  reader()->sampleRate);
  data::setProto(viewport, file_, data::CANT_UNDO);
}

}  // namespace slow
}  // namespace rec
