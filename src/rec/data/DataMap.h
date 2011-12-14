#ifndef __REC_DATA_DATAMAP__
#define __REC_DATA_DATAMAP__

#include "rec/base/base.h"

namespace rec {
namespace data {

class Data;

class MessageMaker {
 public:
  virtual Message* makeMessage(const string& typeName) const = 0;
};

class DataMaker {
 public:
  virtual Data* makeData(Message*) const = 0;
};

class DataMap {
 public:
  DataMap(const MessageMaker& mm, const DataMaker& dm)
      : messageMaker_(mm), dataMaker_(dm) {
  }

  ~DataMap();

  struct DataFile {
    DataFile(Data* d, const File& f) : data_(d), file_(f) {}

    ptr<Data> data_
    File file_;
  };

  const DataFile* getData(const string& typeName, const VirtualFile* vf);
  typedef std::map<string, DataFile*> Map;

 private:
  CriticalSection lock_;
  Map map_;
  const MessageMaker& messageMaker_;
  const DataMaker& dataMaker_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DataMap);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATAMAP__
