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
  TableModel(const TableColumnList& c, const Address& addr, const Address& sel)
      : TableModelBase(c, addr, sel), AddressListener<Proto>(addr) {
  }

  virtual void setData(Data* data) { setSetter(data); }
  virtual const Value get() const { return TableModelBase::get(); }
  virtual void set(const Value& v) { TableModelBase::set(v); }

 protected:
  virtual const Message& message() const { return proto_; }
  virtual Message* mutable_message() { return &proto_; }
  virtual const Address& address() const {
    return AddressListener<Proto>::address();
  }

  virtual void setSelected(int index, bool selected) {
    ScopedLock l(lock_);
    if (setter_) {
      Address addr = address();
      addr.add_field()->set_index(index);
      if (setter_->getValue(addr).bool_f() != selected) {
        setter_->set(addr, selected);
        Operation op;
        op.set_command(Operation::SET);
        op.mutable_address()->CopyFrom(addr);
        ptr<Operation> undo(proto::applyOperation(op, mutable_message()));
      }
    }
  }

 private:
  Proto proto_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TableModel);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TABLEMODEL__
