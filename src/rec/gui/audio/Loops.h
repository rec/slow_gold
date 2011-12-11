#ifndef __REC_GUI_AUDIO_LOOPS__
#define __REC_GUI_AUDIO_LOOPS__

#include "rec/data/Address.h"
#include "rec/gui/TableController.h"
#include "rec/gui/component/Focusable.h"
#include "rec/util/Cuttable.h"
#include "rec/util/DataListener.h"
#include "rec/util/LoopPoint.pb.h"

namespace rec {
namespace gui {
namespace audio {

class Loops : public component::Focusable<TableController>,
              public DataListener<LoopPointList>,
              public HasCuttable {
 public:
  explicit Loops(MenuBarModel* menus, const TableColumnList* desc = NULL,
                 const data::Address& partAddress = data::Address("loop_point"),
                 const data::Address& baseAddress =
                 data::Address::default_instance());
  virtual ~Loops();

  virtual Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected,
                                             Component* existingComponentToUpdate);

  virtual void onDataChange(const LoopPointList&);
  virtual int getNumRows() { return getProto().loop_point_size(); }
  virtual Cuttable* cuttable() { return cuttable_.get(); }
  virtual void selectedRowsChanged(int lastRowSelected);

 protected:
  virtual void update();
  virtual String displayText(const TableColumn& col, int row);

 private:
  LoopPointList loops_;
  data::Address partAddress_;
  ptr<Cuttable> cuttable_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Loops);
};

}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_GUI_AUDIO_LOOPS__
