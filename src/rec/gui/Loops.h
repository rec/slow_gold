#ifndef __REC_GUI_LOOPS__
#define __REC_GUI_LOOPS__

#include "rec/audio/source/Segment.pb.h"
#include "rec/gui/TableModel.h"

namespace rec {
namespace gui {

typedef audio::source::SegmentList SegmentList;
typedef TableModel<SegmentList> LoopsBase;

class Loops : public LoopsBase {
 public:
  explicit Loops(const TableColumnList* desc = NULL);
  virtual ~Loops() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(Loops);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_LOOPS__
