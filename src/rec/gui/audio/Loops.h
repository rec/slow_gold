#ifndef __REC_GUI_AUDIO_LOOPS__
#define __REC_GUI_AUDIO_LOOPS__

#include "rec/data/Address.h"
#include "rec/data/Value.h"
#include "rec/gui/TableController.h"
#include "rec/gui/component/Focusable.h"
#include "rec/util/Cuttable.h"
#include "rec/util/LoopPoint.pb.h"
#include "rec/util/Math.h"
#include "rec/util/Range.h"
#include "rec/util/DataListener.h"
#include "rec/util/Listener.h"
#include "rec/widget/waveform/Waveform.h"

namespace rec {
namespace gui {
namespace audio {

bool isNewLoopPointTime(const LoopPointList& lp, RealTime t);

class Loops : public component::Focusable<TableController>,
              public DataListener<LoopPointList>,
              public Cuttable {
 public:
  explicit Loops(MenuBarModel* menus, const TableColumnList* desc = NULL,
                const data::Address& address = data::Address("loop_point"));
  virtual ~Loops();

  static const RealTime CLOSE;

  virtual void onDataChange(const LoopPointList&);

  virtual int getNumRows() {
    return get().loop_point_size();
 }

  double near(double x, double y) const { return util::near(x, y, CLOSE); }

  virtual bool canCopy() const;
  virtual bool canPaste() const { return true; }
  virtual bool canCut() const { return canCopy(); }
  virtual string copy() const;
  virtual bool paste(const string&);
  virtual void cut();

  bool isNewLoopPoint(RealTime t) const;
  void addLoopPoint(RealTime time);
  void addLoopPoints(const LoopPointList& loops);
  void setLoopPoints(const LoopPointList& loops);

  virtual void selectedRowsChanged(int lastRowSelected);

  const string cuttableName() const { return "Loops"; }

 protected:
  virtual void update();
  virtual String displayText(const TableColumn& col, int row);

 private:
  LoopPointList getSelected(bool selected) const;

  DISALLOW_COPY_AND_ASSIGN(Loops);
};

}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_GUI_AUDIO_LOOPS__
