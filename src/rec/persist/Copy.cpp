#include <google/protobuf/text_format.h>

#include "rec/base/base.h"
#include "rec/persist/Copy.h"
#include "glog/logging.h"
#include "rec/base/scoped_ptr.h"

namespace rec {
namespace persist {

using google::protobuf::TextFormat;

namespace {

template <typename Type>
bool doCopy(const Type& to, Type* from) {
  *from = to;
  return true;
}

template <typename From, typename To>
bool doCopy(const From& from, To* to) {
  std::string through;
  return copy(from, &through) && copy(through, to);
}

}  // namespace

bool copy(const Message& from, string* to) {
  return TextFormat::PrintToString(from, to);
}

bool copy(const string& from, Message* to) {
  return TextFormat::ParseFromString(from, to);
}

// Now, specify copies to and from std::string.
bool copy(const string &from, String *to) {
  *to = copy(from);
  return true;
}

bool copy(const String &from, string *to) {
  *to = copy(from);
  return true;
}

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

bool copy(const String &f, String *t) { return doCopy(f, t); }
bool copy(const String &f, File *t) { return doCopy(f, t); }
bool copy(const File &f, String *t) { return doCopy(f, t); }
bool copy(const File &f, Message *t) { return doCopy(f, t); }
bool copy(const String &f, Message *t) { return doCopy(f, t); }
bool copy(const Message &f, String *t) { return doCopy(f, t); }
bool copy(const Message &f, File *t) { return doCopy(f, t); }
bool copy(const string &f, string *t) { return doCopy(f, t); }

bool copy(const File &f, File *t) {
  return f.copyFileTo(*t);
}

bool copy(const Message &f, Message *t) {
  t->CopyFrom(f);
  return true;
}

}  // namespace persist
}  // namespace rec

