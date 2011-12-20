#ifndef __REC_DATA_DATAIMPL__
#define __REC_DATA_DATAIMPL__

#include "rec/data/Data.h"
#include "rec/data/DataMaker.h"
#include "rec/data/DataUpdater.h"
#include "rec/data/UndoStack.h"

namespace rec {
namespace data {

class DataImpl : public Data, public DataMaker {
 public:
  DataImpl(Message*, const File&, DataUpdater*, UndoStack*);
  virtual ~DataImpl() {}

  virtual void pushOnUndoStack(const Message& before);
  virtual void reportChange();
  virtual bool update();
  virtual void clearRecentListeners();
  virtual bool writeToFile();
  virtual bool fileReadSuccess() const { return fileReadSuccess_; }

  virtual void addListener(Listener<const Message&>*);
  virtual void removeListener(Listener<const Message&>*);

  virtual Data* makeData(Message*, const File&) const;

 private:
  typedef std::set<Listener<const Message&>*> ListenerSet;

  ListenerSet recentListeners_;
  File file_;
  DataUpdater* dataUpdater_;
  UndoStack* undoStack_;

  bool alreadyReadFromFile_;
  bool fileReadSuccess_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(DataImpl);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATAIMPL__
