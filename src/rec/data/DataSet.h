#pragma once

#include <set>

#include "rec/data/Data.h"
#include "rec/util/HasLock.h"

namespace rec {
namespace data {

class DataSet : public HasLock {
  public:
    DataSet() : thread_(nullptr) {}

    using Set = std::set<Data*>;
    Set* release();
    void insert(Data* data);
    int insert(Set* s);
    bool hasUpdates() const;

  private:
    void notify();

    std::unique_ptr<Set> data_;
    Thread* thread_;
    CriticalSection lock_;

};

}  // namespace data
}  // namespace rec
