#ifndef __REC_GUI_TABLEMODEL__
#define __REC_GUI_TABLEMODEL__

#include "rec/data/persist/Persist.h"
#include "rec/util/listener/AddressListener.h"
#include "rec/gui/TableModelBase.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

using proto::Operation;

template <typename Proto>
class TableModel : public TableModelBase, public AddressListener<Proto> {
 public:
  typedef persist::Data<Proto> Data;
  TableModel(const TableColumnList& c, const Address& addr, const Address& sel)
      : TableModelBase(c), AddressListener<Proto>(addr), selected_(sel) {
  }

  virtual void setData(Data* data) {
    ScopedLock l(lock_);
    DataListener<Proto>::setData(data);
    if (data)
      proto_ = data->get();
    else
      proto_.Clear();
    thread::callAsync(this, &TableListBox::updateContent);
  }

  void repaint() { TableModelBase::repaint(); }

  virtual const Value get() const {
    ScopedLock l(lock_);
    Value value;
    proto_.SerializeToString(value.mutable_message_f());
    return value;
  }

  virtual void set(const Value& v) {
    ScopedLock l(lock_);

    if (!proto_.ParseFromString(v.message_f()))
      LOG(ERROR) << "Couldn't parse value: " << proto_.DebugString();
  }

 protected:
  virtual const Message& message() const { return proto_; }
  virtual const Address& address() const {
    return AddressListener<Proto>::address();
  }

  virtual void selectedRowsChanged(const juce::SparseSet<int>& selected) {
    for (int i = 0, done = 0; i < selected.getNumRanges(); ++i) {
      juce::Range<int> range = selected.getRange(i);
      for (; done < range.getStart(); ++done)
        setSelected(done, false);

      for (; done != range.getEnd(); ++done)
        setSelected(done, true);
    }
  }

  void setSelected(int index, bool selected) {
    Data* data = this->getData();
    if (data) {
      Address addr = address();
      addr.add_field()->set_index(index);
      if (data->getValue(addr).bool_f() != selected) {
        data->set(addr, selected);
        Operation op;
        op.set_command(Operation::SET);
        op.mutable_address()->CopyFrom(addr);
        ptr<Operation> undo(proto::applyOperation(op, &proto_));
      }
    }
  }

 private:
  Proto proto_;
  Address selected_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(TableModel);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TABLEMODEL__
