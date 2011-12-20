#ifndef __REC_DATA_DATA__
#define __REC_DATA_DATA__

#include <google/protobuf/message.h>

#include "rec/util/Listener.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

class DataUpdater;
class DataImpl;

template <typename Proto> class Opener;

class Data : public Broadcaster<const Message&> {
 public:
  virtual bool fileReadSuccess() const = 0;

 private:
  Data(Message* m) : message_(m) {}
  virtual ~Data() {}

  // Report a change to the protocol buffer.
  virtual void pushOnUndoStack(const Message& before) = 0;
  virtual void reportChange() = 0;
  virtual bool update() = 0;
  virtual void clearRecentListeners() = 0;
  virtual bool writeToFile() = 0;

  CriticalSection lock_;
  ptr<Message> message_;
  bool clientsNeedUpdate_;

  friend class DataImpl;
  friend class DataMapImpl;
  friend class DataUpdater;

  template <typename Proto> friend class Reader;
  template <typename Proto> friend class Opener;
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATA__
