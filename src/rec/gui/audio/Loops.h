#ifndef __REC_GUI_AUDIO_LOOPS__
#define __REC_GUI_AUDIO_LOOPS__

#include "rec/util/LoopPoint.pb.h"
#include "rec/util/listener/DataListener.h"
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

class LoopPointDataListener;

class Loops : public component::Focusable<TableController>, public Cuttable {
 public:
  explicit Loops(ApplicationCommandManager* manager,
                 const TableColumnList* desc = NULL);
  virtual ~Loops();

  static const double CLOSE;

  virtual int getNumRows() {
    ScopedLock l(lock_);
    return std::max(0, loopPoints_->loop_point_size() - 1);
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
  void setLoopPoints(const LoopPointList& loops) { *loopPoints_ = loops; updateAndRepaint(); }
  Range<RealTime> selectionRange() const;

  virtual void selectedRowsChanged(int lastRowSelected);

  const string cuttableName() const { return "Loops"; }

 protected:
  virtual void update();

 private:
  double length_;
  LoopPointList* loopPoints_;
  ptr<LoopPointDataListener> dataListener_;

  DISALLOW_COPY_AND_ASSIGN(Loops);
};


}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_GUI_AUDIO_LOOPS__
