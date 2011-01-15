#ifndef __REC_GUI_TABLEMODELBASE__
#define __REC_GUI_TABLEMODELBASE__

#include "rec/base/Base.h"
#include "rec/gui/TableColumn.pb.h"
#include "rec/util/Reference.h"

namespace rec {
namespace gui {

class TableModelBase :
    public juce::TableListBoxModel,
    public juce::TableListBox {
 public:
  TableModelBase(const TableColumnList& columns);

  virtual void fillHeader(TableHeaderComponent* headers);
  virtual int getNumRows();
  virtual void paintRowBackground(Graphics& g, int row, int w, int h, bool sel);
  virtual void paintCell(Graphics& g, int r, int c, int w, int h, bool sel);

  virtual void selectedRowsChanged(int lastRowSelected) {
    selectedRowsChanged(getSelectedRows());
  }

  void repaint() { TableListBox::repaint(); }

  const Value get() const;
  void set(const Value& v);

 protected:
  virtual const Message& message() const = 0;
  virtual Message* mutable_message() = 0;
  virtual const Address& address() const = 0;
  virtual void setSelected(int index, bool selected) = 0;

  void selectedRowsChanged(const juce::SparseSet<int>& selected);
  static String displayText(const TableColumn& col, const Value& value);

  const TableColumnList columns_;
  CriticalSection lock_;
  // ptr<Message> proto_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(TableModelBase);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TABLEMODELBASE__
