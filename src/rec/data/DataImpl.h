#ifndef __REC_DATA_DATAIMPL__
#define __REC_DATA_DATAIMPL__

#include "rec/data/Data.h"
#include "rec/data/DataMaker.h"
#include "rec/data/DataUpdater.h"
#include "rec/data/UndoStack.h"

namespace rec {
namespace data {

class DataImpl : public Data, public DataMaker {
 public:
  DataImpl(Message *m, DataUpdater* u, UndoStack* s)
      : Data(m), dataUpdater_(u), undoStack_(s) {
  }

  virtual void pushOnUndoStack(const Message& before) {
    undoStack_->push(this, before, *message_);
  }

  virtual void reportChange() const {
    dataUpdater_->reportChange(this);
  }

  virtual Data* makeData(Message* m) const {
    return new DataImpl(m, undoStack_, dataUpdater_);
  }

 private:
  UndoStack* undoStack_;
  DataUpdater* dataUpdater_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(DataImpl);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATAIMPL__
