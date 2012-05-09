#ifndef __REC_DATA_DATASET__
#define __REC_DATA_DATASET__

#include <set>

#include "rec/util/HasLock.h"
#include "rec/data/DataUpdater.h"

namespace rec {
namespace data {

class DataSet : public HasLock {
 public:
  DataSet() : thread_(NULL) {}

  typedef std::set<Data*> Set;
  Set* transfer();
  void insert(Data* data);
  int insert(Set* s);
  bool hasUpdates() const;

 private:
  void notify();

  ptr<Set> data_;
  Thread* thread_;
  CriticalSection lock_;

};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATASET__
