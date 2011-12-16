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
  DataImpl(Message*, DataUpdater*, UndoStack*);
  virtual ~DataImpl() {}

  virtual void pushOnUndoStack(const Message& before);
  virtual void reportChange() const;
  virtual bool update();
  virtual void clearRecentListeners();

  virtual void addListener(const Listener<const Message&>*);
  virtual void removeListener(const Listener<const Message&>*);

  virtual Data* makeData(Message*) const;

 private:
  typedef std::set<Listener<const Message&> > ListenerSet;

  ListenerSet recentListeners_;
  UndoStack* undoStack_;
  DataUpdater* dataUpdater_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(DataImpl);
};

}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATAIMPL__
