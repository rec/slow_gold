#include "rec/slow/Instance.h"

#include "rec/app/AppSettings.pb.h"
#include "rec/app/GenericApplication.h"
#include "rec/app/RegisterInstance.h"
#include "rec/audio/Device.h"
#include "rec/audio/OutputSampleRate.h"
#include "rec/audio/source/FrameSource.h"
#include "rec/audio/source/Player.h"
#include "rec/audio/util/BufferFiller.h"
#include "rec/audio/util/BufferedReader.h"
#include "rec/audio/util/FillerThread.h"
#include "rec/base/Arraysize.h"
#include "rec/base/DropDead.h"
#include "rec/base/SampleRate.h"
#include "rec/command/Command.pb.h"
#include "rec/command/KeyboardBindings.h"
#include "rec/command/map/MidiCommandMap.h"
#include "rec/data/DataCenter.h"
#include "rec/data/DataOps.h"
#include "rec/data/Opener.h"
#include "rec/data/UndoStack.h"
#include "rec/gui/Dialog.h"
#include "rec/gui/LookAndFeel.h"
#include "rec/gui/proto/Help.h"
#include "rec/program/JuceModel.h"
#include "rec/slow/Components.h"
#include "rec/slow/CurrentFile.h"
#include "rec/slow/CurrentTime.h"
#include "rec/slow/GuiListener.h"
#include "rec/slow/GuiSettings.h"
#include "rec/slow/MouseListener.h"
#include "rec/slow/SlowWindow.h"
#include "rec/slow/commands/Command.pb.h"
#include "rec/slow/commands/SlowProgram.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/Undo.h"
#include "rec/util/ews/EWS.h"
#include "rec/util/file/FileType.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/thread/Trash.h"
#include "rec/widget/tree/Root.h"
#include "rec/widget/tree/TreeViewDropAll.h"
#include "rec/widget/waveform/Cursor.h"

namespace rec {
namespace slow {

using namespace rec::app;
using namespace rec::audio::source;
using namespace rec::audio::util;
using namespace rec::audio;
using namespace rec::widget::waveform;

using gui::DialogLocker;

static const int MS_TILL_TOOLTIP = 700;
static const int FILLER_PRIORITY = 4;

using juce::TooltipWindow;

namespace {

#if JUCE_WINDOWS

struct FileAssociation {
  String extension_, symbolicName_, fullName_;
  void registerExtension(const String& exe) {
    juce::WindowsRegistry::registerFileAssociation(
        extension_, symbolicName_, fullName_, exe, 0, false);
  }
};

FileAssociation FILES[] = {
  { ".aif", "aiff", "Audio IFF files" },
  { ".aiff", "aiff", "Audio IFF files" },
  { ".mp3", "mp3", "MP3 files" },
  { ".wav", "wave", "Microsoft WAVE documents" },
  { ".wave", "wave", "Microsoft WAVE documents" },
  { ".slow", "SlowGold", "World-Wide Woodshed SlowGold 8 documents" }
};

#endif  // JUCE_WINDOWS

class RegisterSlow : public app::RegisterInstance {
 public:
  RegisterSlow() {}

  virtual void onSuccess() {
    data::Opener<AppSettings> settings(data::global(), data::CANT_UNDO);
    settings->set_registered(true);
#if JUCE_WINDOWS
    if (!settings->windows_registered()) {
      String exe = File::getSpecialLocation(File::currentExecutableFile).
        getFullPathName();
      for (int i = 0; i < arraysize(FILES); ++i)
        FILES[i].registerExtension(exe);
      settings->set_windows_registered(true);
    }
#endif  // JUCE_WINDOWS
  }
};

Instance* INSTANCE = nullptr;

}  // namespace

Instance* getInstance() {
  return INSTANCE;
}

const VirtualFile getInstanceFile() {
  return INSTANCE->file();
}

Instance::Instance(app::Window* window) : window_(window) {
  CHECK_DDD(51, 2193, int64, int32);
  logDropDead();
  DCHECK(!INSTANCE);
  INSTANCE = this;
}

void Instance::init() {
  slowProgram_.reset(new SlowProgram(this));
  juceModel_.reset(new program::JuceModel(slowProgram_.get()));
  juceModel_->init();

  window_->init();
  device_.reset(new audio::Device);
  currentFile_.reset(new CurrentFile);

  player_.reset(new audio::source::Player(device_.get()));

  player_->init();
  components_.reset(new Components);
  components_->init();

  currentTime_.reset(new CurrentTime);
  bufferFiller_.reset(new BufferFiller);
  lookAndFeel_.reset(new gui::LookAndFeel);
  mouseListener_.reset(new MouseListener);
  guiListener_.reset(new GuiListener);
  fillerThread_.reset(
      new FillerThread(currentTime_.get(), bufferFiller_.get()));

  midiCommandMap_.reset(new command::MidiCommandMap);


  device_->manager_.addMidiInputCallback("",  midiCommandMap_.get());
  midiCommandMap_->addCommands(data::getProto<command::CommandMapProto>());

  program::applicationCommandManager()->setFirstCommandTarget(
      juceModel_.get());
  window_->addKeyListener(program::applicationCommandManager()->getKeyMappings());

  fillerThread_->setPriority(FILLER_PRIORITY);

  program::applicationCommandManager()->registerAllCommandsForTarget(juceModel_.get());
  command::loadKeyboardBindings(program::applicationCommandManager());
  window_->getAppleMenu()->addCommandItem(program::applicationCommandManager(),
                                          slow::Command::ABOUT_THIS_PROGRAM);

  audio::getOutputSampleRateBroadcaster()->addListener(player_.get());

  player_->setSource(makeSource());
  components_->waveform()->setAudioThumbnail(bufferFiller_->thumbnail());

  DialogLocker::getDisableBroadcaster()->addListener(juceModel_.get());
  DialogLocker::getDisableBroadcaster()->addListener(window_->application());

#ifdef DRAW_LOOP_POINTS_IS_ONE_CLICK
  Mode mode = data::getProto<Mode>();
  if (mode.click() == Mode::DRAW_LOOP_POINTS) {
    mode.clear_click();
    setProto(mode);
  }
#endif
}

Instance::~Instance() {
  currentFile_->saveState();
  device_->manager_.removeMidiInputCallback("", midiCommandMap_.get());
  player_->setState(audio::transport::STOPPED);
  device_->shutdown();
}

audio::Source* Instance::makeSource() const {
  return bufferFiller_->reader()->makeSource();
}

bool Instance::startup() {
  juceModel_->menuItemsChanged();

  VirtualFile vf = data::getProto<VirtualFile>();
  if (vf.type() != VirtualFile::NONE) {
    File f = file::toRealFile(vf);
    vf = file::toVirtualFile(f);
    data::setProto(vf);
  }

  {
    MessageManagerLock l;
    juce::LookAndFeel::setDefaultLookAndFeel(lookAndFeel_.get());

    window_->toFront(true);
    currentFile_->setVirtualFile(vf, false);
  }

  thread::callAsync(window_, &DocumentWindow::setVisible, true);
  juceModel_->startThreads();
  broadcastState<Thread*>(juceModel_->getThread("timer"));

  data::getDataCenter()->undoStack()->setEnabled();
  if (!data::getProto<AppSettings>().registered())
    thread::trash::run<RegisterSlow>();

  if (data::getProto<GuiSettings>().show_about_on_startup() or
      not ews::testAuthenticated().authenticated()) {
    MessageManagerLock l;
    window_->startAboutWindow();
  }
  return true;
}

const VirtualFile Instance::file() const {
  return currentFile_->file();
}

void Instance::updateGui() {
  guiListener_->update();
}

SampleTime Instance::length() const {
  return currentFile_->length();
}

SampleTime Instance::time() const {
  return currentTime_->time();
}

bool Instance::isPlaying() const {
  return player_ && player_->state();
}

bool Instance::empty() const {
  return currentFile_ && currentFile_->empty();
}

void Instance::setProto(const Message& m, data::Undoable undoable) {
   data::setProto(m, file(), undoable);
   juceModel_->menuItemsChanged();
}

static const int FILLER_THREAD_STOP_TIME = 60000;

void Instance::reset() {
  player_->reset();
  fillerThread_->stopThread(FILLER_THREAD_STOP_TIME);
  bufferFiller_->reset();
  currentTime_->reset();
}

void Instance::shutdown() {
  juceModel_->stopThreads();
  reset();
}

SampleRate Instance::getSourceSampleRate() const {
  return data::getProto<Viewport>(file()).loop_points().sample_rate();
}

}  // namespace slow
}  // namespace rec
