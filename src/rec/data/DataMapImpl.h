#pragma once

#include <map>

#include "rec/data/DataMap.h"

namespace rec {

namespace util { class MessageMaker; }

namespace data {

class Data;
class DataMaker;

class DataMapImpl : public DataMap {
  public:
    explicit DataMapImpl(MessageMaker* m, DataMaker* d);
    virtual ~DataMapImpl();

    virtual Data* getData(const string& typeName, const VirtualFile& vf);
    virtual void removeData(Data*);
    virtual void updateAll();

  private:
    struct DataRecord;
    typedef std::map<string, DataRecord*> Map;

    MessageMaker* messageMaker_;
    DataMaker* dataMaker_;
    Map map_;

    CriticalSection lock_;
    DISALLOW_COPY_ASSIGN_AND_LEAKS(DataMapImpl);
};

}  // namespace data
}  // namespace rec
