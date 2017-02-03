#pragma once

#include "rec/data/Reader.h"
#include "rec/data/Undoable.h"
#include "rec/util/proto/Proto.h"

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

  Opener(Undoable undoable = CAN_UNDO) : Reader<Proto>(), undoable_(undoable) {
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
  std::unique_ptr<Message> before_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(Opener);
};

}  // namespace data
}  // namespace rec
