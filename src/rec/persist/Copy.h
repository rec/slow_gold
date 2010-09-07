#ifndef __REC_PERSIST_COPY__
#define __REC_PERSIST_COPY__

#include <string>
#include "google/protobuf/message.h"
#include "google/protobuf/text_format.h"

#include "JuceLibraryCode/JuceHeader.h"

// A generic function to copy "anything" to "anything else".
// Example: read a protocol message from a file.
//
//
//
// Specific implementations exist for all pairs of:
//   std::string
//   Juce::String
//   Juce::File
//   google::protobuf::Message
//
// In the case of protobufs, we use human-readable form for the serialization
// and deserialization.

#if 0
namespace std {
class string;
}

namespace google {
namespace protobuf {

class Messsage;
class TextFormat;

}  // namespace protobuf
}  // namespace google

#endif

namespace rec {
namespace persist {

typedef google::protobuf::Message Message;
typedef std::string string;

bool copy(const File& from, File* to);
bool copy(const File& from, Message* to);
bool copy(const File& from, String* to);
bool copy(const File& from, string* to);

bool copy(const Message& from, File* to);
bool copy(const Message& from, Message* to);
bool copy(const Message& from, String* to);
bool copy(const Message& from, string* to);

bool copy(const String& from, File* to);
bool copy(const String& from, Message* to);
bool copy(const String& from, String* to);
bool copy(const String& from, string* to);

bool copy(const string& from, File* to);
bool copy(const string& from, Message* to);
bool copy(const string& from, String* to);
bool copy(const string& from, string* to);

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_COPY__
