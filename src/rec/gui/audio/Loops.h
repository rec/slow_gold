#ifndef __REC_GUI_AUDIO_LOOPS__
#define __REC_GUI_AUDIO_LOOPS__

#include "rec/data/Address.h"
#include "rec/gui/TableController.h"
#include "rec/util/Cuttable.h"
#include "rec/data/DataListener.h"
#include "rec/util/LoopPoint.pb.h"

namespace rec {
namespace gui {
namespace audio {

class Loops : public TableController,
              public DataListener<LoopPointList>,
              public HasCuttable {
 public:
  explicit Loops(const TableColumnList* desc = NULL,
                 const data::Address& partAddress = data::Address("loop_point"));
  virtual ~Loops();

  virtual Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected,
                                             Component* existingComponentToUpdate);

  virtual void operator()(const LoopPointList& lpl) { setLoops(lpl); }
  virtual int getNumRows();
  virtual Cuttable* cuttable() { return cuttable_.get(); }
  virtual void selectedRowsChanged(int lastRowSelected);

  void editLoopPoints(const LoopPointList&);

 protected:
  virtual void update();
  virtual String displayText(const TableColumn& col, int row);

 private:
  void setLoops(const LoopPointList&);

  LoopPointList loops_;
  data::Address partAddress_;
  ptr<Cuttable> cuttable_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Loops);
};

}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_GUI_AUDIO_LOOPS__
