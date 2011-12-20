#ifndef __REC_DATA_DATAMAPIMPL__
#define __REC_DATA_DATAMAPIMPL__

#include <map>

#include "rec/data/DataMap.h"

namespace rec {
namespace data {

class Data;
class DataMaker;
class MessageMaker;

class DataMapImpl : public DataMap {
 public:
  explicit DataMapImpl(MessageMaker* m, DataMaker* d);
  virtual ~DataMapImpl();

  virtual Data* getData(const string& typeName, const VirtualFile* vf);

 private:
  struct DataFile;
  typedef std::map<string, DataFile*> Map;

  MessageMaker* messageMaker_;
  DataMaker* dataMaker_;
  Map map_;

  CriticalSection lock_;
  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataMapImpl);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATAMAPIMPL__
