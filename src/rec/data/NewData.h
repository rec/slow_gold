#ifndef __REC_DATA_NEWDATA__
#define __REC_DATA_NEWDATA__

#include "rec/util/Listener.h"

namespace rec {
namespace data {

class Data : public Broadcaster<const Message&> {
 public:
  explicit Data(Message* m) : message_(m) {}
  virtual ~Data() {}

  Message* clone() const { return message_ ? message_->New() : NULL; }

 private:
  // Update any clients, probably in another thread.
  virtual void updateClients() = 0;

  ptr<Message> message_;

  template <typename Proto> friend class Opener;
};

template <typename Proto>
bool applyToData(bool (*function)(Proto*), Data* data) {
  return function(Opener<Proto>(data).get());
}

template <typename Proto, typename Functor>
bool applyToData(Functor functor, Data* data) {
  return functor(Opener<Proto>(data).get());
}


template <typename Proto>
void set(const Proto& p, const VirtualFile& f = file::none(),
         bool undoable = true) {
  editable<Proto>(f)->setValue(p, Address::default_instance(), undoable);
}


  template <typename Function> bool apply(Function f) {
    return f(get());
  }



struct Data : public MessageBroadcaster {
  Data() {}
  virtual ~Data() {}
};

template <typename Proto>
bool apply(Data* data, bool (*function)(Proto*)) {
  Lock l(data->lock());

  ptr<Message> message(data->getMessage());
  if (Proto* proto = dynamic_cast<Proto*>(message.get()))
    return function(proto) && setMessage(*message);

  LOG(DFATAL) << getTypeName<Proto> << "!= " << getTypeName(*message);
  return false;
}


]
template <typename Proto>
void set(const Proto& p, const VirtualFile& f, bool undoable = true) {
  editable<Proto>(f)->setValue(p, Address::default_instance(), undoable);
}



}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_NEWDATA__
