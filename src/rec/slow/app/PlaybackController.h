#ifndef __REC_SLOW_APP_PLAYBACKCONTROLLER__
#define __REC_SLOW_APP_PLAYBACKCONTROLLER__

#include "rec/gui/Layout.h"
#include "rec/gui/SetterTextArea.h"
#include "rec/gui/StretchyController.h"
#include "rec/util/listener/DataListener.h"
#include "rec/slow/app/TimeController.h"
#include "rec/util/cd/Album.h"

namespace rec {
namespace slow {

typedef audio::source::StretchyProto StretchyProto;
typedef widget::status::time::TextComponent TextComponent;
typedef widget::status::time::DialComponent DialComponent;

class PlaybackController : public gui::Layout,
                           public Listener<const VolumeFile&>,
                           public Listener<float>,
                           public Broadcaster<float>,
                           public DataListener<StretchyProto> {
 public:
  typedef persist::Data<StretchyProto> Data;

  PlaybackController();

  virtual void operator()(float time);
  virtual void operator()(const VolumeFile&);
  virtual void operator()(const StretchyProto&);

  virtual void setData(Data* data);

  void resized();
  TimeController* timeController() { return &timeController_; }

 private:
  gui::StretchyController stretchyController_;
  gui::SetterTextArea<cd::Metadata> songData_;
  TimeController timeController_;

  DISALLOW_COPY_AND_ASSIGN(PlaybackController);
};

}  // namespace slow
}  // namespace rec

#endif  // __REC_SLOW_APP_PLAYBACKCONTROLLER__
