#ifndef __REC_DATA_OPENER__
#define __REC_DATA_OPENER__

#include "rec/data/Reader.h"

namespace rec {
namespace data {

template <typename Proto>
struct Opener : public Reader<Proto> {
  Opener(Data* d, Undoable undoable = CAN_UNDO)
      : Reader<Proto>(d),
        undoable_(undoable) {
    initialize();
  }

  Opener(VirtualFile* vf, Undoable undoable = CAN_UNDO)
      : Reader<Proto>(vf),
        undoable_(undoable) {
    initialize();
  }

  ~Opener() {
    if (changed_) {
      if (undoable_ == CAN_UNDO)
        this->data_->pushOnUndoStack(*before_);
      this->data_->reportChange();
    }
  }

  Proto& operator*() { return *mutable_get(); }
  Proto* operator->() { return mutable_get(); }

  Proto* mutable_get() {
    changed_ = true;
    return this->proto_;
  }

 private:
  void initialize() {
    changed_ = false;
    before_.reset(this->cloneMessage());
    before_->CopyFrom(*this->proto_);
  }

  bool changed_;
  const Undoable undoable_;
  ptr<Message> before_;
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_OPENER__
