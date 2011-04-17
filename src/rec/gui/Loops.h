#ifndef __REC_GUI_LOOPS__
#define __REC_GUI_LOOPS__

#include "rec/gui/LoopPoint.pb.h"
#include "rec/gui/TableController.h"
#include "rec/util/Cuttable.h"
#include "rec/util/Math.h"
#include "rec/util/Range.h"
#include "rec/util/listener/Listener.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace gui {

class Loops : public TableController,
              public Cuttable,
              public Listener<const widget::waveform::CursorTime&> {
 public:
  explicit Loops(const TableColumnList* desc = NULL);
  virtual ~Loops();

  static const double CLOSE;

  double near(double x, double y) const { return util::near(x, y, CLOSE); }

  virtual void onDataChange();
  void doSelect();
  virtual bool canCopy() const;
  virtual bool canPaste() const { return true; }
  virtual string copy() const;
  virtual bool paste(const string&);
  virtual void cut();

  void setLength(int len);
  bool isNewLoopPoint(double t) const;
  void addLoopPoint(double time);
  TimeRange selectionRange() const;
  void clearSelection();
  void clearLoops();

  virtual void selectedRowsChanged(int lastRowSelected);
  virtual bool keyPressed(const juce::KeyPress& kp);
  virtual void operator()(const widget::waveform::CursorTime&);

  Broadcaster<double>* timeBroadcaster() { return &timeBroadcaster_; }

 private:
  double length_;
  LoopPointList loopPoints_;
  Broadcaster<double> timeBroadcaster_;

  DISALLOW_COPY_AND_ASSIGN(Loops);
};


}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_LOOPS__
