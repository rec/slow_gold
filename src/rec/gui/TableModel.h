#ifndef __REC_GUI_TABLEMODEL__
#define __REC_GUI_TABLEMODEL__

#include "rec/data/persist/Persist.h"
#include "rec/util/listener/AddressListener.h"
#include "rec/gui/TableController.h"

namespace rec {
namespace gui {

using proto::Operation;

template <typename Proto>
class TableModel : public TableController, public AddressListener<Proto> {
 public:
  typedef persist::Data<Proto> Data;
  TableModel(const TableColumnList& c, const Address& address)
      : TableController(c, address), AddressListener<Proto>(Address()) {
  }

  virtual void setData(Data* data) {
    setSetter(data);
    AddressListener<Proto>::setData(data);
  }

  virtual const Value get() const { return TableController::get(); }
  virtual void set(const Value& v) { TableController::set(v); }

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
