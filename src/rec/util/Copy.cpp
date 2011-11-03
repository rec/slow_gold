#include <google/protobuf/text_format.h>

#include "rec/base/base.h"
#include "rec/util/Copy.h"
#include "glog/logging.h"

using google::protobuf::TextFormat;
using namespace juce;

namespace rec {
namespace copy {

namespace {

// Copy using assignment.
template <typename Type>
bool assign(const Type& from, Type* to, bool /* readable */) {
  *to = from;
  return true;
}

// Copy using the one-argument copy() function.
bool strcopy(const String& from, string* to, bool /* readable */) {
  *to = str(from);
  return true;
}

// Copy using the one-argument copy() function.
bool strcopy(const string& from, String* to, bool /* readable */) {
  *to = str(from);
  return true;
}

// Copy through an string.
template <typename From, typename To>
bool through(const From& from, const To& to, bool readable) {
  string thr;
  return copy(from, &thr, readable) && copy(thr, to, readable);
}

// Copy through an string.
template <typename From, typename To>
bool through(const From& from, To* to, bool readable) {
  string thr;
  return copy(from, &thr, readable) && copy(thr, to, readable);
}

// Copy using googlebase::proto functions.
bool proto(const Message& f, string* t, bool readable) {
  try {
    return readable ? TextFormat::PrintToString(f, t) : f.SerializeToString(t);
  } catch (...) {
    return false;
  }
}

bool proto(const string& f, Message* t, bool readable) {
  try {
    return readable ? TextFormat::ParseFromString(f, t) : t->ParseFromString(f);
  } catch (...) {
    return false;
  }
}

bool proto(const Message& f, Message* t, bool /* readable */) {
  try {
    t->CopyFrom(f);
    return true;
  } catch (...) {
    return false;
  }
}

bool file(const File &f, File *t, bool /* readable */) {
  return f.copyFileTo(*t);
}

bool file(const File &f, const File& t, bool /* readable */) {
  return f.copyFileTo(t);
}

bool file(const File &file, string *s, bool /* readable */) {
  try {
    ptr<FileInputStream> in(file.createInputStream());
    if (!in)
      return false;
    uint length = static_cast<uint>(in->getTotalLength());
    // TODO: deal with long buffers.
    s->resize(length);
    int bytesRead = in->read((void*)s->data(), length);
    LOG_IF(ERROR, bytesRead < 0) << "negative bytes read.";
    s->resize(bytesRead);

    return true;
  } catch (...) {
    return false;
  }
}

bool file(const string &from, const File &to, bool /* readable */) {
  try {
    if (!to.getParentDirectory().createDirectory()) {
      LOG(ERROR) << "Couldn't create directory for " << str(to);
      return false;
    }

    bool rename = to.exists();
    File backupFile;
    if (rename) {
      backupFile = File(to.getFullPathName() + ".bak");
      if (!to.moveFileTo(backupFile))
        LOG(ERROR) << "Couldn't rename to backup file: " << str(backupFile);
    }

    ptr<FileOutputStream> out(to.createOutputStream());
    if (!out)
      LOG(ERROR) << "Couldn't make OutputStream for " << str(to);

    else if (!out->write(from.data(), from.size()))
      LOG(ERROR) << "Couldn't write file " << str(to);

    else if (rename && !backupFile.deleteFile())
      LOG(ERROR) << "Couldn't delete backup " << str(to);

    else
      return true;

  } catch (...) {
    LOG(ERROR) << "We got an exception";
    // TODO: log this exception here.
  }
  return false;
}

typedef MemoryBlock Memory;

bool memory(const string& in, Memory* out, bool /* readable */) {
  int size = in.size();
  out->ensureSize(size);
  out->copyFrom(in.data(), 0, size);
  return true;
}

bool memory(const Memory& in, string* out, bool /* readable */) {
  int size = in.getSize();
  out->resize(size);
  in.copyTo(&((*out)[0]), 0, size);
  return true;
}

}  // namespace

bool copy(const File &f,    File *t,    bool r) { return file(f, *t, r); }
bool copy(const File &f,    Memory *t,  bool r) { return through(f, t, r); }
bool copy(const File &f,    Message *t, bool r) { return through(f, t, r); }
bool copy(const File &f,    String *t,  bool r) { return through(f, t, r); }
bool copy(const File &f,    string *t,  bool r) { return file(f, t, r); }

bool copy(const Memory &f,  File *t,    bool r) { return through(f, t, r); }
bool copy(const Memory &f,  Memory *t,  bool r) { return assign(f, t, r); }
bool copy(const Memory &f,  Message *t, bool r) { return through(f, t, r); }
bool copy(const Memory &f,  String *t,  bool r) { return through(f, t, r); }
bool copy(const Memory &f,  string *t,  bool r) { return memory(f, t, r); }

bool copy(const Message &f, File *t,    bool r) { return through(f, t, r); }
bool copy(const Message &f, Memory *t,  bool r) { return through(f, t, r); }
bool copy(const Message &f, Message *t, bool r) { return proto(f, t, r); }
bool copy(const Message &f, String *t,  bool r) { return through(f, t, r); }
bool copy(const Message &f, string *t,  bool r) { return proto(f, t, r); }

bool copy(const String &f,  File *t,    bool r) { return through(f, t, r); }
bool copy(const String &f,  Memory *t,  bool r) { return through(f, t, r); }
bool copy(const String &f,  Message *t, bool r) { return through(f, t, r); }
bool copy(const String &f,  String *t,  bool r) { return assign(f, t, r); }
bool copy(const String &f,  string *t,  bool r) { return strcopy(f, t, r); }

bool copy(const string &f,  File *t,    bool r) { return file(f, *t, r); }
bool copy(const string &f,  Memory *t,  bool r) { return memory(f, t, r); }
bool copy(const string &f,  Message *t, bool r) { return proto(f, t, r); }
bool copy(const string &f,  String *t,  bool r) { return strcopy(f, t, r); }
bool copy(const string &f,  string *t,  bool r) { return assign(f, t, r); }

bool copy(const File &f,    const File &t, bool r) { return file(f, t, r); }
bool copy(const string &f,  const File &t, bool r) { return file(f, t, r); }
bool copy(const String &f,  const File &t, bool r) { return through(f, t, r); }
bool copy(const Message &f, const File &t, bool r) { return through(f, t, r); }
bool copy(const Memory &f,  const File &t, bool r) { return through(f, t, r); }

}  // namespace copy
}  // namespace rec

