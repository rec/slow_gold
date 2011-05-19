#ifndef __REC_GUI_AUDIO_LOOPS__
#define __REC_GUI_AUDIO_LOOPS__

#include "rec/gui/audio/LoopPoint.pb.h"
#include "rec/gui/TableController.h"
#include "rec/gui/component/Focusable.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Math.h"
#include "rec/util/Range.h"
#include "rec/util/listener/Listener.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace gui {
namespace audio {

bool isNewLoopPointTime(const LoopPointList& lp, RealTime t);

class Loops : public component::Focusable<TableController>, public Cuttable {
 public:
  explicit Loops(const TableColumnList* desc = NULL,
                 bool allowDiscontinuousSelections = true);
  virtual ~Loops();

  static const double CLOSE;

  int getNumRows() {
    ScopedLock l(lock_);
    return loopPoints_->loop_point_size();
  }

  double near(double x, double y) const { return util::near(x, y, CLOSE); }

  virtual bool canCopy() const;
  virtual bool canPaste() const { return true; }
  virtual bool canCut() const { return canCopy(); }
  virtual string copy() const;
  virtual bool paste(const string&);
  virtual void cut();

  void setLength(int len);
  bool isNewLoopPoint(RealTime t) const;
  void addLoopPoint(RealTime time);
  void addLoopPoints(const LoopPointList& loops);
  TimeRange selectionRange() const;
  void clearSelection();
  void clearLoops();

  void paint(Graphics& g) {
    component::Focusable<TableController>::paint(g);
    DLOG(INFO) << "Here! " << loopPoints_->DebugString();
  }

  virtual void selectedRowsChanged(int lastRowSelected);

  const string cuttableName() const { return "Loops"; }

 protected:
  virtual void update();

 private:
  double length_;
  LoopPointList* loopPoints_;
  const bool allowDiscontinuousSelections_;

  DISALLOW_COPY_AND_ASSIGN(Loops);
};


}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_GUI_AUDIO_LOOPS__
