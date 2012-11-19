#ifndef __REC_UTIL_DELETABLESET__
#define __REC_UTIL_DELETABLESET__

#include "rec/util/Deletable.h"
#include "rec/util/STL.h"

namespace rec {
namespace util {

class DeletableSet {
 public:
  DeletableSet() {}
  ~DeletableSet() {
    stl::deletePointers(&set_);
  }
  void insert(Deletable* del) { set_.insert(del); }

 private:
  typedef std::set<Deletable> Set;

  Set set_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(DeletableSet);
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_DELETABLESET__
