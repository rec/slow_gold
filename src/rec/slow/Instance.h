#ifndef __REC_SLOW_INSTANCE__
#define __REC_SLOW_INSTANCE__

#include "rec/app/Window.h"
#include "rec/audio/Audio.h"
#include "rec/base/SampleRate.h"
#include "rec/base/SampleTime.h"
#include "rec/util/thread/Trash.h"

namespace rec {

namespace audio { class Device; }
namespace command { class CommandData; }
namespace command { class CommandRecordTable; }
namespace command { class MidiCommandMap; }
namespace audio { namespace source { class Player; }}
namespace audio { namespace util { class BufferFiller; }}
namespace gui { class LookAndFeel; }

// Test stuff!
namespace program { class JuceModel; }

namespace slow {

class Components;
class CurrentFile;
class CurrentTime;
class FillerThread;
class GuiListener;
class Menus;
class MouseListener;
class SlowWindow;
class Threads;

class SlowProgram;

// A single instance of the Slow program.  Right now there's only one per
// application but in future there might be more than one.
class Instance {
 public:
  explicit Instance(app::Window*);
  ~Instance();

  void init();
  void startup();
  void postStartup();

  const VirtualFile file() const;
  SampleTime time() const;
  SampleTime length() const;
  bool isPlaying() const;
  void updateGui();
  bool empty() const;
  audio::Source* makeSource() const;
  SampleRate getSourceSampleRate() const;
  void setProto(const Message&, Undoable undoable = CAN_UNDO);
  void reset();

  static const int FILLER_THREAD_STOP_TIME = 60000;

  app::Window* window_;
  CriticalSection lock_;

  ptr<audio::Device> device_;
  ptr<audio::util::BufferFiller> bufferFiller_;
  ptr<CurrentFile> currentFile_;

  ptr<audio::source::Player> player_;
  ptr<Components> components_;
  ptr<CurrentTime> currentTime_;

  ptr<MouseListener> mouseListener_;
  ptr<GuiListener> guiListener_;
  ptr<Threads> threads_;
  thread_ptr<Thread> fillerThread_;
  ptr<gui::LookAndFeel> lookAndFeel_;
  ptr<command::MidiCommandMap> midiCommandMap_;

  ptr<command::CommandRecordTable> commandRecordTable_;
  ptr<command::CommandData> commandData_;

  static Instance* getInstance();
  static const VirtualFile getInstanceFile();

  Listener<Enable>* enableListener();
  Listener<CommandID>* idListener();

 private:
  unique_ptr<SlowProgram> slowProgram_;
  unique_ptr<program::JuceModel> juceModel_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Instance);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_INSTANCE__
