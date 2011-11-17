#ifndef __REC_GUI_TABLEMODELBASE__
#define __REC_GUI_TABLEMODELBASE__

#include "rec/base/RealTime.h"
#include "rec/gui/TableColumn.pb.h"
#include "rec/util/listener/ProtoListener.h"
#include "rec/data/Address.h"

namespace rec {
namespace gui {

class TableController : public TableListBoxModel, public TableListBox {
 public:
  TableController();

  void initialize(const TableColumnList& columns,
                  const data::Address& address,
                  const char* name);

  virtual void fillHeader(TableHeaderComponent* headers);
  virtual int getNumRows() = 0;
  virtual void paintRowBackground(Graphics& g, int row, int w, int h, bool sel);
  virtual void paintCell(Graphics& g, int r, int c, int w, int h, bool sel);

  virtual void selectedRowsChanged(int lastRowSelected) = 0;

  void updateAndRepaint() { update(); repaint(); }
  void setLength(RealTime len) { length_ = len; }

 protected:
  virtual void update() { updateContent(); }
  virtual String displayText(const TableColumn& col, int row) = 0;

  ptr<Message> message_;
  TableColumnList columns_;
  CriticalSection lock_;

  data::Address address_;
  RealTime length_;

 private:
  DISALLOW_COPY_AND_ASSIGN(TableController);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TABLEMODELBASE__
