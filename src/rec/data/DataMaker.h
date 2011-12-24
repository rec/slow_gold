#ifndef __REC_DATA_DATAMAKER__
#define __REC_DATA_DATAMAKER__

#include "rec/base/base.h"

namespace rec {
namespace data {

class Data;

class DataMaker {
 public:
  DataMaker() {}
  virtual ~DataMaker() {}

  virtual Data* makeData(Message*, const File&, bool isEmpty) const = 0;
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATAMAKER__
