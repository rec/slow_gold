#ifndef __REC_PERSIST_COPY__
#define __REC_PERSIST_COPY__

#include <string>
#include <google/protobuf/message.h>

#include "rec/base/base.h"

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

bool copy(const File& from, File* to, bool readable = true);
bool copy(const File& from, const File& to, bool readable = true);
bool copy(const File& from, MemoryBlock* to, bool readable = true);
bool copy(const File& from, Message* to, bool readable = true);
bool copy(const File& from, String* to, bool readable = true);
bool copy(const File& from, string* to, bool readable = true);

bool copy(const Message& from, File* to, bool readable = true);
bool copy(const Message& from, const File& to, bool readable = true);
bool copy(const Message& from, MemoryBlock* to, bool readable = true);
bool copy(const Message& from, Message* to, bool readable = true);
bool copy(const Message& from, String* to, bool readable = true);
bool copy(const Message& from, string* to, bool readable = true);

bool copy(const MemoryBlock& from, File* to, bool readable = true);
bool copy(const MemoryBlock& from, const File& to, bool readable = true);
bool copy(const MemoryBlock& from, MemoryBlock* to, bool readable = true);
bool copy(const MemoryBlock& from, Message* to, bool readable = true);
bool copy(const MemoryBlock& from, String* to, bool readable = true);
bool copy(const MemoryBlock& from, string* to, bool readable = true);

bool copy(const String& from, File* to, bool readable = true);
bool copy(const String& from, const File& to, bool readable = true);
bool copy(const String& from, MemoryBlock* to, bool readable = true);
bool copy(const String& from, Message* to, bool readable = true);
bool copy(const String& from, String* to, bool readable = true);
bool copy(const String& from, string* to, bool readable = true);

bool copy(const string& from, File* to, bool readable = true);
bool copy(const string& from, const File& to, bool readable = true);
bool copy(const string& from, MemoryBlock* to, bool readable = true);
bool copy(const string& from, Message* to, bool readable = true);
bool copy(const string& from, String* to, bool readable = true);
bool copy(const string& from, string* to, bool readable = true);

}  // namespace persist
}  // namespace rec

#endif  // __REC_PERSIST_COPY__
