#ifndef __REC_PERSIST_COPY__
#define __REC_PERSIST_COPY__

namespace rec {
namespace persist {

template <typename From, typename To>
bool copy(const From& from, To* to);

template <typename From, typename Through, typename To>
bool copy(const From& from, Through through, To* to) {
  return copy(from, &through) && copy(through, to);
}

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_COPY__
