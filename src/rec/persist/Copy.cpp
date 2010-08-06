#include "rec/persist/Copy.h"
#include "google/protobuf/message.h"
#include "google/protobuf/text_format.h"
#include "glog/logging.h"
#include "rec/base/scoped_ptr.h"

#include "juce_amalgamated.h"

namespace rec {
namespace persist {

using std::string;

template <>
bool copy(const File &file, string *s) {
  scoped_ptr<FileInputStream> in(file.createInputStream());
  if (!in) {
    LOG(ERROR) << "Couldn't read file " << file.getFileName();
    return false;
  }
  int64 length = in->getTotalLength();
  s->resize(length);
  int bytesRead = in->read((void*)s->data(), length);
  LOG_IF(ERROR, bytesRead < 0) << "negative bytes read.";
  s->resize(bytesRead);

  return true;
}

template <>
bool copy(const string &from, const File* to) {
  scoped_ptr<FileOutputStream> out(to->createOutputStream());
  if (!out) {
    LOG(ERROR) << "Couldn't write file " << to->getFileName();
    return false;
  }

  return out->write(from.data(), from.size());
}

template <>
bool copy(const google::protobuf::Message &from, string *to) {
  return google::protobuf::TextFormat::PrintToString(from, to);
}

template <>
bool copy(const string &from, google::protobuf::Message *to) {
  return google::protobuf::TextFormat::ParseFromString(from, to);
}

template <>
bool copy(const File &from, google::protobuf::Message *to) {
  return copy(from, string(), to);
}

template <>
bool copy(const google::protobuf::Message &from, const File *to) {
  return copy(from, string(), to);
}


template <>
bool copy(const string &from, String *to) {
  *to = String(from.data(), from.size());
  return true;
}

template <>
bool copy(const String &from, string *to) {
  *to = string(from.toCString(), from.toCString() + from.length());
  return true;
}

template <> bool copy(const string &from, string *to);
template <> bool copy(const String &from, String *to);

}  // namespace persist
}  // namespace rec

