#pragma once

#include <google/protobuf/message.h>

#include "rec/util/Listener.h"
#include "rec/util/file/VirtualFile.h"
#include "rec/util/proto/Proto.h"

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

    string getTypeName() const {
        Lock l(lock_);
        return message_->GetTypeName();
    }
    virtual const string& key() const = 0;

    Message* clone() const {
        Lock l(lock_);
        return util::clone(message_.get());
    }

    virtual void addListener(Listener<const Message&>* listener) {
        Broadcaster<const Message&>::addListener(listener);
        // (*listener)(*std::unique_ptr<Message>(clone()));  // OH, DEAR!
    }

  protected:
    CriticalSection lock_;

  private:
    Data(bool isEmpty) : changed_(false), isEmpty_(isEmpty) {}
    virtual ~Data() {}

    // Report a change to the protocol buffer.
    virtual void pushOnUndoStack(const Message& before) = 0;
    virtual void reportChange() = 0;
    virtual bool writeToFile() = 0;
    virtual void update() = 0;

    std::unique_ptr<Message> message_;

    bool changed_;
    const bool isEmpty_;

    friend class DataImpl;
    friend class DataMapImpl;
    friend class DataUpdater;

    template <typename Proto> friend class Reader;
    template <typename Proto> friend class Opener;
};

Data* getData(const string& typeName, const VirtualFile& vf);

// The virtual file for global data (not attached to any specific file).
const VirtualFile& global();

// The virtual file for empty data (not stored or updated).
const VirtualFile& noData();

template <typename Proto>
Data* getData(const VirtualFile& vf) {
    return getData(getTypeName<Proto>(), vf);
}

inline Data* getData(const Message& m, const VirtualFile& vf) {
    return getData(m.GetTypeName(), vf);
}

inline const VirtualFile& global() {
    static const VirtualFile vf = file::makeVirtualFile(VirtualFile::GLOBAL);
    return vf;
}

inline const VirtualFile& noData() {
    static const VirtualFile vf;
    return vf;
}


}  // namespace data
}  // namespace rec
