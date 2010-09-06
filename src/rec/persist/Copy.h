#ifndef __REC_PERSIST_COPY__
#define __REC_PERSIST_COPY__

#include <string>

// Copy "anything" to "anything else".
//
// Specific implementations exist for all pairs of:
//   std::string
//   Juce::String
//   Juce::File
//   google::protobuf::Message
//
// In the case of protobufs, we use human-readable form for the serialization
// and deserialization.

namespace rec {
namespace persist {

template <typename From, typename To>
bool copy(const From& from, To* to) {
  std::string through;
  return copy(from, &through) && copy(through, to);
}

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_COPY__
