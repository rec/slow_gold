#include "rec/util/proto/ProtoFile.h"

#include "rec/util/Copy.h"
#include "rec/util/proto/MessageMaker.h"
#include "rec/util/proto/Proto.h"

namespace rec {
namespace util {

Message* readProtoFile(const File& file, const MessageMaker& maker) {
  ptr<Message> msg;
  StringArray lines;
  file.readLines(lines);
  if (lines.size()) {
    string type = str(lines[0]);
    msg.reset(maker.makeMessage(type));
    lines.remove(0);
    if (!copy::copy(lines.joinIntoString("\n"), msg.get())) {
      LOG(DFATAL) << "Couldn't read file of type " << type;
      msg.reset();
    }
  }

  return msg.transfer();
}

void writeProtoFile(const Message& msg, const File& file) {
  string s;
  if (!(copy::copy(msg, &s) &&
        copy::copy(str(getTypeName(msg) + "\n" + s), file))) {
    LOG(ERROR) << "Unable to write proto file " << str(file);
  }
}

}  // namespace util
}  // namespace rec
