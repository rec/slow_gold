#ifndef __REC_SLOW_APP_PLAYBACKCONTROLLER__
#define __REC_SLOW_APP_PLAYBACKCONTROLLER__

#include "rec/gui/Layout.h"
#include "rec/gui/SetterTextArea.h"
#include "rec/gui/SongData.h"
#include "rec/slow/TimeController.h"

namespace rec {
namespace gui {
namespace audio {

class PlaybackController : public Layout {
 public:
  typedef proto::arg::Address Address;
  explicit PlaybackController(Instance* i,
                              const Address& a = Address::default_instance());

  void setSetter(persist::Setter* setter);

 private:
  Layout panel_;

  SetterResizer timeControllerResizer_;
  SetterResizer songDataResizer_;
  SetterResizer stretchyResizer_;

  DISALLOW_COPY_AND_ASSIGN(PlaybackController);
};

}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_SLOW_APP_PLAYBACKCONTROLLER__
