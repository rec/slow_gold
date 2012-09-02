#include "rec/util/proto/ReadProtoFile.h"

#include "rec/util/Copy.h"
#include "rec/util/proto/MessageMaker.h"

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

}  // namespace util
}  // namespace rec
