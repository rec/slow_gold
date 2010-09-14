#ifndef __REC_PERSIST_COPY__
#define __REC_PERSIST_COPY__

#include <string>
#include "google/protobuf/message.h"

#include "JuceLibraryCode/JuceHeader.h"

// A set of overloaded functions to copy "anything" to "anything else".
//
// Example: read a protocol message from a file.
//   MyProto proto;
//   if (!rec::persist::copy(File(myFileName), &proto)) {
//     // Handle error.
//   }
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

typedef google::protobuf::Message Message;
typedef std::string string;

bool copy(const File& from, File* to, bool readable = true);
bool copy(const File& from, Message* to, bool readable = true);
bool copy(const File& from, String* to, bool readable = true);
bool copy(const File& from, string* to, bool readable = true);

bool copy(const Message& from, File* to, bool readable = true);
bool copy(const Message& from, Message* to, bool readable = true);
bool copy(const Message& from, String* to, bool readable = true);
bool copy(const Message& from, string* to, bool readable = true);

bool copy(const String& from, File* to, bool readable = true);
bool copy(const String& from, Message* to, bool readable = true);
bool copy(const String& from, String* to, bool readable = true);
bool copy(const String& from, string* to, bool readable = true);

bool copy(const string& from, File* to, bool readable = true);
bool copy(const string& from, Message* to, bool readable = true);
bool copy(const string& from, String* to, bool readable = true);
bool copy(const string& from, string* to, bool readable = true);

// Useful copiers for string and String.
inline String copy(const string& s) { return String(s.data(), s.size()); }
inline string copy(const String& s) { return string(s.toCString(), s.length()); }

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_COPY__
