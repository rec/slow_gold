#ifndef __REC_DATA_DATAMAKERIMPL__
#define __REC_DATA_DATAMAKERIMPL__

#include "rec/data/DataImpl.h"
#include "rec/data/DataMaker.h"

namespace rec {
namespace data {

class DataMakerImpl : public DataMaker {
 public:
  DataMakerImpl(DataUpdater* u, UndoStack* s)
      : dataUpdater_(u), undoStack_(s) {
  }

  virtual ~DataMakerImpl() {}

  virtual Data* makeData(Message* m) const {
    return new DataImpl(m, undoStack_, dataUpdater_);
  }

 private:
  UndoStack* undoStack_;
  DataUpdater* dataUpdater_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataMakerImpl);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATAMAKERIMPL__
