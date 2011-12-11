#ifndef __REC_GUI_AUDIO_LOOPSCUTTABLE__
#define __REC_GUI_AUDIO_LOOPSCUTTABLE__

#include "rec/util/Cuttable.h"

namespace rec {
namespace gui {
namespace audio {

class Loops;

class LoopsCuttable : public Cuttable {
 public:
  LoopsCuttable(Loops* loops) : loops_(loops) {}
  virtual ~LoopsCuttable() {}

  virtual bool canCopy() const;
  virtual bool canPaste() const;
  virtual bool canCut() const;
  virtual string copy() const;
  virtual bool paste(const string&);
  virtual void cut();

  const string cuttableName() const { return "Loops"; }

 private:
  Loops* loops_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(LoopsCuttable);
};

}  // namespace audio
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_AUDIO_LOOPSCUTTABLE__
