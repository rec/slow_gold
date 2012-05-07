#ifndef __REC_DATA_DATA__
#define __REC_DATA_DATA__

#include <google/protobuf/message.h>

#include "rec/util/Listener.h"
#include "rec/util/Proto.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

class DataUpdater;
class DataImpl;

template <typename Proto> class Opener;

class Data : public Broadcaster<const Message&> {
 public:
  virtual bool fileReadSuccess() const = 0;
  virtual const string toString() const = 0;
  virtual const File getFile() const = 0;

  bool isEmpty() const { return isEmpty_; }
  const string& getTypeName() const {
    Lock l(lock_);
    return util::getTypeName(*message_);
  }
  virtual const string& key() const = 0;

  Message* clone() const {
    Lock l(lock_);
    return util::clone(*message_);
  }

  virtual void addListener(Listener<const Message&>* listener) {
    Broadcaster<const Message&>::addListener(listener);
    (*listener)(*ptr<Message>(clone()));
  }
  virtual void update() = 0;

 protected:
  CriticalSection lock_;

 private:
  Data(bool e) : changed_(false), isEmpty_(e) {}
  virtual ~Data() {}

  // Report a change to the protocol buffer.
  virtual void pushOnUndoStack(const Message& before) = 0;
  virtual void reportChange() = 0;
  virtual bool writeToFile() = 0;

  ptr<Message> message_;

  bool changed_;
  const bool isEmpty_;

  friend class DataImpl;
  friend class DataMapImpl;
  friend class DataUpdater;

  template <typename Proto> friend class Reader;
  template <typename Proto> friend class Opener;
};

Data* getData(const string& typeName, const VirtualFile* vf);

template <typename Proto>
Data* getData(const VirtualFile* vf) {
  return getData(getTypeName<Proto>(), vf);
}

inline Data* getData(const Message& m, const VirtualFile* vf) {
  return getData(getTypeName(m), vf);
}

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATA__
