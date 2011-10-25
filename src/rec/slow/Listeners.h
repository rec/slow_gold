#ifndef __REC_SLOW_LISTENERS__
#define __REC_SLOW_LISTENERS__

#include "rec/audio/Audio.h"
#include "rec/command/Command.pb.h"
#include "rec/slow/HasInstance.h"
#include "rec/util/Range.h"
#include "rec/util/listener/Listener.h"

namespace rec {

namespace audio { namespace stretch { class Stretch; }}
namespace audio { namespace source { class StereoProto; }}

namespace gui { class DropFiles; }

namespace util { class LoopPointList; }
namespace util { namespace file { class VirtualFile; }}
namespace util { namespace file { class VirtualFileList; }}

namespace widget { namespace waveform { class ZoomProto; }}

namespace slow {

class Instance;
class MouseListener;

class Listeners : public Listener<audio::transport::State>,
                  public Listener<const gui::DropFiles&>,
                  public juce::MouseListener,
                  public HasInstance {
 public:
  explicit Listeners(Instance* i);
  virtual ~Listeners();

  virtual void operator()(audio::transport::State);
  virtual void operator()(const gui::DropFiles&);

 private:
  ptr<slow::MouseListener> mouseListener_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Listeners);
};

}  // namespace slow1
}  // namespace rec

#endif  // __REC_SLOW_LISTENERS__
