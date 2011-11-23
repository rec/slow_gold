#include <set>

#include "rec/util/UpdateRequester.h"

namespace rec {
namespace util {

namespace {

class UpdateRequests {
 public:
  UpdateRequests() {}
  ~UpdateRequests() {}

  void add(UpdateRequester* requester) {
    Lock l(lock_);
    requesters_.insert(requester);
  }

  void requestAllUpdates() {
    RequesterSet req;
    {
      Lock l(lock_);
      req.swap(requesters_);
    }

    for (RequesterSet::iterator i = req.begin(); i != req.end(); ++i)
      (*i)->requestUpdates();
  }

 private:
  typedef std::set<UpdateRequester*> RequesterSet;
  RequesterSet requesters_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(UpdateRequests);
};

UpdateRequests* requests() {
  static UpdateRequests requests;
  return &requests;
}

}  // namespace


UpdateRequester::UpdateRequester() {
  requests()->add(this);
}

void UpdateRequester::requestAllUpdates() {
  requests()->requestAllUpdates();
}

}  // namespace util
}  // namespace rec
