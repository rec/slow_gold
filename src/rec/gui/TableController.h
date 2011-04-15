#ifndef __REC_GUI_TABLEMODELBASE__
#define __REC_GUI_TABLEMODELBASE__

#include "rec/base/Base.h"
#include "rec/gui/TableColumn.pb.h"
#include "rec/util/listener/ProtoAddressListener.h"
#include "rec/util/Reference.h"
#include "rec/data/proto/Address.h"

namespace rec {
namespace gui {

class TableController : public TableListBoxModel,
                        public TableListBox,
                        public ProtoAddressListener {
 public:
  TableController(const TableColumnList& columns, const Address& address,
                  const char* name = "TableController");

  virtual void fillHeader(TableHeaderComponent* headers);
  virtual int getNumRows();
  virtual void paintRowBackground(Graphics& g, int row, int w, int h, bool sel);
  virtual void paintCell(Graphics& g, int r, int c, int w, int h, bool sel);

  virtual void setData(UntypedData* data);

  const Value get() const;
  void set(const Value& v);

  virtual void selectedRowsChanged(int lastRowSelected) = 0;
  void repaint() { TableListBox::repaint(); }

 protected:
  // onDataChange() is called to update the GUI when the persistent data
  // underlying this GUI component changes
  virtual void onDataChange();

  static String displayText(const TableColumn& col, const Value& value);

  ptr<Message> message_;
  const TableColumnList columns_;
  CriticalSection lock_;

  Address address_;
  int numRows_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(TableController);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TABLEMODELBASE__
