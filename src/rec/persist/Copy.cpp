#include "rec/base/base.h"
#include "rec/persist/Copy.h"
#include "google/protobuf/message.h"
#include "google/protobuf/text_format.h"
#include "glog/logging.h"
#include "rec/base/scoped_ptr.h"

#include "JuceLibraryCode/JuceHeader.h"

namespace rec {
namespace persist {

using std::string;

template <>
bool copy(const File &file, string *s) {
  scoped_ptr<FileInputStream> in(file.createInputStream());
  if (!in) {
    LOG(WARNING) << "Couldn't read file " << file.getFullPathName();
    return false;
  }
  int64 length = in->getTotalLength();
  s->resize(length);
  int bytesRead = in->read((void*)s->data(), length);
  LOG_IF(FATAL, bytesRead < 0) << "negative bytes read.";
  s->resize(bytesRead);

  return true;
}

template <>
bool copy(const string &from, File *to) {
  if (!to->getParentDirectory().createDirectory()) {
    LOG(FATAL) << "Couldn't create directory for "
                << to->getFullPathName().toCString();
    return false;
  }

  bool rename = to->exists();
  File backupFile;
  if (rename) {
    backupFile = File(to->getFullPathName() + ".bak");
    if (!to->moveFileTo(backupFile)) {
      LOG(FATAL) << "Couldn't rename to backup file: "
                  << backupFile.getFullPathName();
    }
  }

  scoped_ptr<FileOutputStream> out(to->createOutputStream());
  if (!out) {
    LOG(FATAL) << "Couldn't create OutputStream for " << to->getFullPathName();
    return false;
  }

  if (!out->write(from.data(), from.size())) {
    LOG(FATAL) << "Couldn't write file " << to->getFullPathName();
    return false;
  }

  if (rename && !backupFile.deleteFile()) {
    LOG(FATAL) << "Couldn't delete backup " << to->getFullPathName();
    return false;
  }

  return true;
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
bool copy(const google::protobuf::Message &from, File *to) {
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

template <> bool copy(const string &from, string *to) {
  *to = from; return true;
}

template <> bool copy(const String &from, String *to) {
  *to = from; return true;
}

}  // namespace persist
}  // namespace rec

