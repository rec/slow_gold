#ifndef __REC_UTIL_UNTYPEDDATALISTENER__
#define __REC_UTIL_UNTYPEDDATALISTENER__

#include "rec/data/Data.h"
#include "rec/data/Value.h"
#include "rec/util/Listener.h"
#include "rec/util/file/VirtualFile.h"

namespace rec {
namespace data {

class AddressListener;
class GlobalAddressListener;
class UntypedGlobalDataListener;

class UntypedDataListener : public Listener<const Message&> {
 public:
  explicit UntypedDataListener(const string& typeName);
  virtual ~UntypedDataListener();

  void init(Scope);
  virtual void init() { init(FILE_SCOPE); }

  virtual void operator()(const Message& m) = 0;
  Data* getData() const;
  const string& typeName() const { return typeName_; }
  bool isInitialized() const { return initialized_; }
  virtual void wasCleared() {}
  void updateCallback();

 protected:
  CriticalSection lock_;

 private:
  void setData(const Message&);
  void setData(const VirtualFile*);

  struct FileListener;
  friend struct FileListener;

  const string typeName_;
  Data* data_;
  ptr<FileListener> fileListener_;
  bool initialized_;
  ptr<VirtualFile> fileName_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(UntypedDataListener);
};

class UntypedGlobalDataListener : public UntypedDataListener {
 public:
  explicit UntypedGlobalDataListener(const string& typeName)
      :  UntypedDataListener(typeName) {
  }
  virtual ~UntypedGlobalDataListener() {}

  virtual void init() {
    UntypedDataListener::init(GLOBAL_SCOPE);
  }

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(UntypedGlobalDataListener);
};

}  // namespace data

using data::UntypedDataListener;
using data::UntypedGlobalDataListener;

}  // namespace rec

#endif  // __REC_UTIL_UNTYPEDDATALISTENER__
