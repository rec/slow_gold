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

class Loops : public component::Focusable<TableController>,
              public DataListener<LoopPointList>,
              public Cuttable {
 public:
  explicit Loops(MenuBarModel* menus, const TableColumnList* desc = NULL,
                const data::Address& address = data::Address("loop_point"));
  virtual ~Loops();

  virtual Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected,
                                             Component* existingComponentToUpdate);

  virtual void onDataChange(const LoopPointList&);

  virtual int getNumRows() { return data()->get().loop_point_size(); }

  virtual bool canCopy() const;
  virtual bool canPaste() const { return true; }  // TODO
  virtual bool canCut() const;
  virtual string copy() const;
  virtual bool paste(const string&);
  virtual void cut();

  virtual void selectedRowsChanged(int lastRowSelected);

  const string cuttableName() const { return "Loops"; }

 protected:
  virtual void update();
  virtual String displayText(const TableColumn& col, int row);

 private:
  LoopPointList loops_;

  DISALLOW_COPY_AND_ASSIGN(Loops);
};

}  // namespace rec
}  // namespace gui
}  // namespace audio

#endif  // __REC_GUI_AUDIO_LOOPS__
