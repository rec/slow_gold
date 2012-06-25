#ifndef __REC_DATA_OPENER__
#define __REC_DATA_OPENER__

#include "rec/data/Reader.h"
#include "rec/util/Proto.h"

namespace rec {
namespace data {

template <typename Proto>
class Opener : public Reader<Proto> {
 public:
  Opener(Data* d, Undoable undoable = CAN_UNDO)
      : Reader<Proto>(d),
        undoable_(undoable) {
    before_.reset(clone(*this->proto_));
  }

  Opener(const VirtualFile& vf, Undoable undoable = CAN_UNDO)
      : Reader<Proto>(vf),
        undoable_(undoable) {
    before_.reset(clone(*this->proto_));
  }

  ~Opener() {
    if (this->data_->isEmpty()) {
      LOG(ERROR) << "Opening empty data " << this->data_->getTypeName();
    } else {
      if (undoable_ == CAN_UNDO)
        this->data_->pushOnUndoStack(*before_);
      this->data_->reportChange();
    }
  }

  Proto& operator*() { return *mutable_get(); }
  Proto* operator->() { return mutable_get(); }
  Proto* mutable_get() { return this->proto_; }

 private:
  const Undoable undoable_;
  ptr<Message> before_;
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_OPENER__
