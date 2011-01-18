#ifndef __REC_GUI_LOOPS__
#define __REC_GUI_LOOPS__

#include "rec/audio/source/LoopPoint.pb.h"
#include "rec/gui/TableModel.h"
#include "rec/util/Math.h"

namespace rec {
namespace gui {

typedef audio::source::LoopPointList LoopPointList;
typedef audio::source::LoopPoint LoopPoint;
typedef TableModel<LoopPointList> LoopsBase;

class Loops : public LoopsBase {
 public:
  explicit Loops(const TableColumnList* desc = NULL);
  virtual ~Loops() {}

  static const double CLOSE;

  double near(double x, double y) const { return util::near(x, y, CLOSE); }

  void setLength(int len);
  bool isNewLoopPoint(double t) const;
  void addLoopPoint(double time);

 private:
  double length_;

  DISALLOW_COPY_AND_ASSIGN(Loops);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_LOOPS__
