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

  virtual Data* makeData(Message* m, const File& file, bool isEmpty) const {
    DLOG(INFO) << "making data: " << str(file);
    return new DataImpl(m, file, dataUpdater_, undoStack_, isEmpty);
  }

 private:
  DataUpdater* dataUpdater_;
  UndoStack* undoStack_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataMakerImpl);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATAMAKERIMPL__
