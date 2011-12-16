#ifndef __REC_DATA_DATAMAP__
#define __REC_DATA_DATAMAP__

#include "rec/base/base.h"

namespace rec {
namespace data {

class Data;

class DataMap {
 public:
  DataMap() {}
  virtual ~DataMap() {}

  // If the VirtualFile is file::none(), then this represents global Data, but
  // if it's NULL then it represents empty data that is not stored to disk.
  virtual Data* getData(const string& typeName, const VirtualFile*) = 0;
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATAMAP__
