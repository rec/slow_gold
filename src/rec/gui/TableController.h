#ifndef __REC_GUI_TABLEMODELBASE__
#define __REC_GUI_TABLEMODELBASE__

#include "rec/base/Base.h"
#include "rec/gui/TableColumn.pb.h"
#include "rec/util/listener/Listener.h"
#include "rec/util/Reference.h"
#include "rec/data/proto/Address.h"

namespace juce {

template <typename T> class SparseSet;

}

namespace rec {
namespace gui {

class TableController : public TableListBoxModel,
                       public TableListBox,
                       public Broadcaster<const juce::SparseSet<int>&> {
 public:
  TableController(const TableColumnList& columns, const Address& address);

  virtual void fillHeader(TableHeaderComponent* headers);
  virtual int getNumRows();
  virtual void paintRowBackground(Graphics& g, int row, int w, int h, bool sel);
  virtual void paintCell(Graphics& g, int r, int c, int w, int h, bool sel);

  void repaint() { TableListBox::repaint(); }

  const Value get() const;
  void set(const Value& v);

  virtual void setSetter(Setter* setter);

  virtual void selectedRowsChanged(int lastRowSelected);

 protected:
  virtual const Message& message() const = 0;
  virtual Message* mutable_message() = 0;
  virtual void onDataChange();

  static String displayText(const TableColumn& col, const Value& value);

  const TableColumnList columns_;
  CriticalSection lock_;
  Setter* setter_;

  Address address_;
  int numRows_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(TableController);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TABLEMODELBASE__
