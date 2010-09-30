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

class CriticalSection;
class File;
class String;

}  // namespace juce

namespace rec {

typedef google::protobuf::Message Message;
typedef juce::CriticalSection CriticalSection;
typedef juce::File File;
typedef juce::String String;

typedef std::string string;

}  // namespace rec

#endif  // __REC_BASE_BASE__
