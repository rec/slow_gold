#ifndef __REC_DATA_EDITABLE__
#define __REC_DATA_EDITABLE__

#include <map>
#include <set>

#include "rec/data/Address.h"

namespace rec {
namespace data {

class Address;
class AddressProto;
class Editable;
class Operation;
class Operations;
class UntypedEditable;
class Value;
class ValueProto;

typedef std::vector<Operations*> OperationList;
typedef std::map<string, UntypedEditable*> EditableMap;
typedef std::set<UntypedEditable*> EditableSet;
typedef std::vector<Editable*> EditableList;

class Editable {
 public:
  Editable() {}
  virtual ~Editable() {}

  void set(const Value&, const Address& a = Address::default_instance());
  void append(const Value& value, const Address&);

  virtual bool fileReadSuccess() const = 0;
  virtual void applyLater(Operations*) = 0;
  virtual void applyOperations(const Operations& olist,
                               Operations* undoes = NULL) = 0;

  virtual const Value getValue(const Address&) const = 0;
  virtual const string getTypeName() const = 0;
  virtual const VirtualFile& virtualFile() const = 0;
  virtual bool readFromFile() const = 0;
  virtual bool writeToFile() const = 0;

  virtual bool hasValue(const Address&) const = 0;
  virtual void copyTo(Message*) const = 0;
  virtual int getSize(const Address&) const = 0;
  virtual Message* clone() const = 0;
  virtual void needsUpdate() = 0;
};

// There are more setters in archived/OldEditable.h

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_EDITABLE__
