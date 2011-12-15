#ifndef __REC_DATA_DATA__
#define __REC_DATA_DATA__

#include "rec/util/Listener.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

class DataUpdater;
class DataImpl;

template <typename Proto> class Opener;

class Data : public Broadcaster<const Message&> {
 private:
  Data(Message* m) : message_(m) { DCHECK(m); }
  virtual ~Data() {}

  // Report a change to the protocol buffer.
  virtual void addToUndoStack(const Message& before) = 0;
  virtual void reportChange() const = 0;

  CriticalSection lock_;
  ptr<Message> message_;

  friend class DataImpl;
  friend class DataUpdater;

  template <typename Proto>
  friend class Opener;
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATA__
