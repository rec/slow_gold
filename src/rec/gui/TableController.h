#ifndef __REC_GUI_TABLEMODELBASE__
#define __REC_GUI_TABLEMODELBASE__

#include "rec/base/Samples.h"
#include "rec/gui/TableColumn.pb.h"
#include "rec/data/Address.h"

namespace rec {
namespace gui {

class TableController : public TableListBoxModel, public TableListBox {
 public:
  TableController();

  void initialize(const TableColumnList& columns, const char* name);

  virtual void fillHeader(TableHeaderComponent* headers);
  virtual int getNumRows() = 0;
  virtual void paintRowBackground(Graphics& g, int row, int w, int h, bool sel);
  virtual void paintCell(Graphics& g, int r, int c, int w, int h, bool sel);

  virtual void selectedRowsChanged(int lastRowSelected) = 0;

  void updateAndRepaint() { update(); repaint(); }
  const TableColumnList& columns() { return columns_; }
  virtual void resized();

 protected:
  virtual void update() { updateContent(); }
  virtual String displayText(const TableColumn& col, int row) = 0;

  ptr<Message> message_;
  TableColumnList columns_;
  CriticalSection lock_;

  data::Address address_;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(TableController);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TABLEMODELBASE__
