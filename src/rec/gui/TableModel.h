#ifndef __REC_GUI_TABLEMODEL__
#define __REC_GUI_TABLEMODEL__

#include "rec/data/persist/Persist.h"
#include "rec/util/listener/AddressListener.h"
#include "rec/gui/TableModelBase.h"

namespace rec {
namespace gui {

using proto::Operation;

template <typename Proto>
class TableModel : public TableModelBase, public AddressListener<Proto> {
 public:
  typedef persist::Data<Proto> Data;
  TableModel(const TableColumnList& c, const Address& address)
      : TableModelBase(c, address), AddressListener<Proto>(address) {
  }

  virtual void setData(Data* data) {
    setSetter(data);
    AddressListener<Proto>::setData(data);
  }

  virtual const Value get() const { return TableModelBase::get(); }
  virtual void set(const Value& v) { TableModelBase::set(v); }

 protected:
  virtual const Message& message() const { return proto_; }
  virtual Message* mutable_message() { return &proto_; }

  Proto proto_;

 private:
  DISALLOW_COPY_ASSIGN_AND_EMPTY(TableModel);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TABLEMODEL__
