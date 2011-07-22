#ifndef __REC_SLOW_LISTENERS__
#define __REC_SLOW_LISTENERS__

#include "rec/audio/Audio.h"
#include "rec/command/Command.pb.h"
#include "rec/slow/HasInstance.h"
#include "rec/slow/LoopCommands.h"
#include "rec/util/Range.h"
#include "rec/util/listener/Listener.h"

namespace rec {

namespace audio { class Gain; }

namespace audio { namespace stretch { class Stretch; }}
namespace audio { namespace source { class StereoProto; }}

namespace gui { class DropFiles; }

namespace util { class LoopPointList; }
namespace util { class Mode; }
namespace util { namespace file { class VirtualFile; }}
namespace util { namespace file { class VirtualFileList; }}

namespace widget { namespace waveform { class ZoomProto; }}

namespace slow {

class Instance;
class MouseListener;

class Listeners : public Listener<None>,
                  public Listener<const VirtualFileList&>,
                  public Listener<audio::transport::State>,
                  public Listener<command::Command::Type>,
                  public Listener<const Mode&>,
                  public Listener<const audio::Gain&>,
                  public Listener<const audio::stretch::Stretch&>,
                  public Listener<const audio::source::StereoProto&>,
                  public Listener<const gui::DropFiles&>,
                  public juce::MouseListener,
                  public HasInstance {
 public:
  explicit Listeners(Instance* i);
  virtual ~Listeners();

  virtual void operator()(None);
  virtual void operator()(const VirtualFileList&);
  virtual void operator()(audio::transport::State);
  virtual void operator()(command::Command::Type);
  virtual void operator()(const Mode&);
  virtual void operator()(const audio::Gain&);
  virtual void operator()(const audio::source::StereoProto&);
  virtual void operator()(const audio::stretch::Stretch&);
  virtual void operator()(const gui::DropFiles&);

  void operator()(SamplePosition);

 private:
  ptr<slow::MouseListener> mouseListener_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Listeners);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_LISTENERS__
