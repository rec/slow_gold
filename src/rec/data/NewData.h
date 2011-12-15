#ifndef __REC_DATA_NEWDATA__
#define __REC_DATA_NEWDATA__

#include "rec/util/Listener.h"

namespace rec {
namespace data {

class Data : public Broadcaster<const Message&> {
 public:
  explicit Data(Message* m) : message_(m) { DCHECK(m); }
  virtual ~Data() {}

 private:
  // Report a change to the protocol buffer.
  virtual void reportChange(const Message& before, bool undoable) = 0;

  CriticalSection lock_;
  ptr<Message> message_;

  template <typename Proto> friend class Opener;

  friend class DataUpdater;
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_NEWDATA__
