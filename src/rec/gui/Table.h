#ifndef __REC_GUI_TABLE__
#define __REC_GUI_TABLE__

#include "rec/data/persist/Persist.h"
#include "rec/gui/TableColumn.pb.h"
#include "rec/util/listener/DataListener.h"
#include "rec/util/Reference.h"
#include "rec/widget/status/Time.h"

namespace rec {
namespace gui {

typedef proto::arg::Setter Setter;

class TableModelBase : public juce::TableListBoxModel, public Reference<Setter> {
 public:
  TableModelBase(const Address& address, const TableColumnList& columns);
  virtual void fillHeaders(TableHeaderComponent* headers);
  virtual int getNumRows();
  virtual void paintRowBackground(Graphics& g, int row, int w, int h, bool sel);
  virtual void paintCell(Graphics& g, int r, int c, int w, int h, bool sel);

 protected:
  virtual const Message& message() const = 0;

 private:
  String displayText(const TableColumn& col, const Value value);

  persist::Setter* setter_;
  const Address address_;
  const TableColumnList columns_;

  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TableModelBase);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TABLE__
