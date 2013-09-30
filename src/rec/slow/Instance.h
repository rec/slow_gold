#ifndef __REC_SLOW_INSTANCE__
#define __REC_SLOW_INSTANCE__

#include "rec/app/Window.h"
#include "rec/audio/Audio.h"
#include "rec/base/SampleRate.h"
#include "rec/base/SampleTime.h"
#include "rec/gui/GetHelpText.h"
#include "rec/util/thread/Trash.h"

namespace rec { namespace audio { class Device; }}
namespace rec { namespace audio { namespace source { class Player; }}}
namespace rec { namespace audio { namespace util { class BufferFiller; }}}
namespace rec { namespace audio { namespace util { class CurrentTimeBase; }}}
namespace rec { namespace command { class MidiCommandMap; }}
namespace rec { namespace gui { class LookAndFeel; }}

namespace rec {

// Test stuff!
namespace program { class JuceModel; }

namespace slow {

class Components;
class CurrentFile;
class CurrentTime;
class GuiListener;
class MouseListener;
class SlowWindow;

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

  app::Window* window_;
  CriticalSection lock_;

  ptr<audio::Device> device_;
  ptr<audio::util::BufferFiller> bufferFiller_;
  ptr<CurrentFile> currentFile_;

  ptr<audio::source::Player> player_;
  ptr<CurrentTime> currentTime_;

  ptr<MouseListener> mouseListener_;
  ptr<GuiListener> guiListener_;
  thread_ptr<Thread> fillerThread_;
  ptr<gui::LookAndFeel> lookAndFeel_;
  ptr<command::MidiCommandMap> midiCommandMap_;
  ptr<Components> components_;

 private:
  unique_ptr<SlowProgram> slowProgram_;
  unique_ptr<program::JuceModel> juceModel_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Instance);
};

Instance* getInstance();
const VirtualFile getInstanceFile();

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_INSTANCE__
