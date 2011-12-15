#ifndef __REC_DATA_DATAOPS__
#define __REC_DATA_DATAOPS__

#include "rec/base/base.h"

namespace rec {
namespace data {
namespace file {

void set(const Message& m, const VirtualFile* vf, bool undoable = true);

template <typename Proto>
const Proto get(const VirtualFile*);

template <typename Proto>
void apply(void (*function)(Proto*), const VirtualFile*);

template <typename Proto, typename Functor>
void apply(Functor functor, VirtualFile*);

}  // namespace file

namespace global {

void set(const Message& m, bool undoable = true);

template <typename Proto>
const Proto get();

template <typename Proto>
void apply(void (*function)(Proto*));

template <typename Proto, typename Functor>
void apply(Functor functor);

}  // namespace global

namespace empty {

void set(const Message& m, bool undoable = true);

template <typename Proto>
const Proto get();

template <typename Proto>
void apply(void (*function)(Proto*));

template <typename Proto, typename Functor>
void apply(Functor functor);

}  // namespace empty

//
//
//
// Implementations.
//
//
//

namespace file {

Data* getData(const string& typeName, const VirtualFile* vf);

inline Data* getData(const Message& m, const VirtualFile* vf) {
  return getData(getTypeName(m), vf);
}

inline void set(const Message& m, const VirtualFile* vf, bool undoable = true) {
  Opener<Message>(getData(getTypeName(m), vf), undoable)->CopyFrom(m);
}

template <typename Proto>
const Proto get(const VirtualFile* vf) {
  return *Opener<Proto>(getData(getTypeName<Proto>(), vf));
}

template <typename Proto>
void apply(void (*function)(Proto*), const VirtualFile* vf) {
  function(Opener<Proto>(getData(getTypeName<Proto>(), vf)).get());
}

template <typename Proto, typename Functor>
void apply(Functor functor, VirtualFile*);
  functor(Opener<Proto>(getData(getTypeName<Proto>(), vf)).get());
}

}  // namespace file

namespace global {

inline void set(const Message& m, bool u = true) {
  file::set(m, &file::none(), u);
}

template <typename Proto>
const Proto get() {
  return file::get<Proto>(&file::none());
}

template <typename Proto>
void apply(void (*function)(Proto*)) {
  file::apply(function, &file::none());
}

template <typename Proto, typename Functor>
void apply(Functor functor, VirtualFile*);
  file::apply(functor, &file::none());
}

}  // namespace global

namespace empty {

inline void set(const Message& m, bool u = true) {
  file::set(m, NULL, u);
}

template <typename Proto>
const Proto get() {
  return file::get<Proto>(NULL);
}

template <typename Proto>
void apply(void (*function)(Proto*)) {
  file::apply(function, NULL);
}

template <typename Proto, typename Functor>
void apply(Functor functor, VirtualFile*);
  file::apply(functor, NULL);
}


}  // namespace empty
}  // namespace data
}  // namespace rec

#endif  // __REC_DATA_DATAOPS__
