#ifndef __REC_BASE_BASE__
#define __REC_BASE_BASE__

#include <string>

#include "rec/base/disallow.h"
#include "rec/base/scoped_ptr.h"
#include "rec/base/types.h"

namespace google {
namespace protobuf {

class Message;

}  // namespace protobuf
}  // namespace google

namespace juce {

class AudioCDReader;
class AudioFormatReader;
class AudioSourceChannelInfo;
class CriticalSection;
class File;
class ScopedLock;
class StreamingSocket;
class String;
class StringArray;
class StringPairArray;
class Thread;

}  // namespace juce

namespace rec {

typedef google::protobuf::Message Message;

typedef juce::AudioCDReader AudioCDReader;
typedef juce::AudioFormatReader AudioFormatReader;
typedef juce::AudioSourceChannelInfo AudioSourceChannelInfo;
typedef juce::CriticalSection CriticalSection;
typedef juce::File File;
typedef juce::String String;
typedef juce::ScopedLock ScopedLock;
typedef juce::StreamingSocket Socket;
typedef juce::StringArray StringArray;
typedef juce::StringPairArray StringPairArray;
typedef juce::Thread Thread;

typedef std::string string;
typedef unsigned int uint;
}  // namespace rec

#endif  // __REC_BASE_BASE__
