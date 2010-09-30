#include <google/protobuf/text_format.h>

#include "rec/base/base.h"
#include "rec/persist/Copy.h"
#include "glog/logging.h"

namespace rec {
namespace persist {

using google::protobuf::TextFormat;

namespace {

// Copy using assignment.
template <typename Type>
bool assign(const Type& from, Type* to, bool readable) {
  *to = from;
  return true;
}

// Copy using the one-argument copy() function.
template <typename From, typename To>
bool copycopy(const From& from, To* to, bool readable) {
  *to = copy(from);
  return true;
}

// Copy through an string.
template <typename From, typename To>
bool through(const From& from, To* to, bool readable) {
  string thr;
  return copy(from, &thr, readable) && copy(thr, to, readable);
}

// Copy using googlebase::proto functions.
bool proto(const Message& f, string* t, bool readable) {
  return readable ? TextFormat::PrintToString(f, t) : f.SerializeToString(t);
}

bool proto(const string& f, Message* t, bool readable) {
  return readable ? TextFormat::ParseFromString(f, t) : t->ParseFromString(f);
}

bool proto(const Message& f, Message* t, bool readable) {
  t->CopyFrom(f);
  return true;
}

bool file(const File &f, File *t, bool readable) {
  return f.copyFileTo(*t);
}

bool file(const File &file, string *s, bool readable) {
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

bool file(const string &from, File *to, bool readable) {
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

}  // namespace

bool copy(const File &f,    File *t,    bool r) { return file(f, t, r); }
bool copy(const File &f,    Message *t, bool r) { return through(f, t, r); }
bool copy(const File &f,    String *t,  bool r) { return through(f, t, r); }
bool copy(const File &f,    string *t,  bool r) { return file(f, t, r); }

bool copy(const Message &f, File *t,    bool r) { return through(f, t, r); }
bool copy(const Message &f, Message *t, bool r) { return proto(f, t, r); }
bool copy(const Message &f, String *t,  bool r) { return through(f, t, r); }
bool copy(const Message &f, string *t,  bool r) { return proto(f, t, r); }

bool copy(const String &f,  File *t,    bool r) { return through(f, t, r); }
bool copy(const String &f,  Message *t, bool r) { return through(f, t, r); }
bool copy(const String &f,  String *t,  bool r) { return assign(f, t, r); }
bool copy(const String &f,  string *t,  bool r) { return copycopy(f, t, r); }

bool copy(const string &f,  File *t,    bool r) { return file(f, t, r); }
bool copy(const string &f,  Message *t, bool r) { return proto(f, t, r); }
bool copy(const string &f,  String *t,  bool r) { return copycopy(f, t, r); }
bool copy(const string &f,  string *t,  bool r) { return assign(f, t, r); }

}  // namespace persist
}  // namespace rec

