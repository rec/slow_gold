#ifndef __REC_GUI_TABLEMODELBASE__
#define __REC_GUI_TABLEMODELBASE__

#include "rec/base/RealTime.h"
#include "rec/gui/TableColumn.pb.h"
#include "rec/util/listener/ProtoListener.h"
#include "rec/data/Address.h"

namespace rec {
namespace gui {

class TableController : public TableListBoxModel,
                        public TableListBox,
                        public ProtoListener {
 public:
  TableController();

  void initialize(const TableColumnList& columns,
                  const data::Address& address,
                  const char* name = "TableController");

  virtual void fillHeader(TableHeaderComponent* headers);
  virtual int getNumRows() = 0;
  virtual void paintRowBackground(Graphics& g, int row, int w, int h, bool sel);
  virtual void paintCell(Graphics& g, int r, int c, int w, int h, bool sel);

  virtual void setUntypedEditable(data::UntypedEditable* data);

  virtual const data::Value getDisplayValue() const;
  virtual void setDisplayValue(const data::Value& v);

  virtual void selectedRowsChanged(int lastRowSelected) = 0;

  void updateAndRepaint() { update(); repaint(); }
  void setLength(RealTime len) { length_ = len; }


 protected:
  virtual void update() { updateContent(); }

  String displayText(const TableColumn& col, const data::Value& value);

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
