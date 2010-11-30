#include <algorithm>

#include <glog/logging.h>

#include "rec/util/cd/CDDBResponse.h"
#include "rec/util/Exception.h"
#include "rec/util/cd/Socket.h"

using namespace juce;

namespace rec {
namespace util {
namespace cd {

bool oneCDDBResponse(String* data, StringArray* lines) {
  bool wasEmpty = (lines->length() == 0);
  if (stripLines(data, lines)) {
    if (wasEmpty) {
      const String& header = data[0];
      int status = header[0];
      if (status == '5')
        throw Exception("CDDB Error: " + header);

      if (status != '2')
        throw Exception("unexpected response: " + header);

      int more = header[1];
      if (more == '0')
        return false;

      if (more != '1')
        throw Exception("unexpected continuation: " + header);
    }
    if ((*lines)[lines->size() - 1] == ".")
      return false;
  }
  return true;
}

StringArray readCDDBResponse(Socket *sock) {
  String data;
  StringArray lines;
  while (readSocket(sock, &data), !oneCDDBResponse(&data, &lines));
  return lines;
}

StringArray makeCDDBRequest(const String& request, Socket *s) {
  return (writeSocket(s, request + "\n"), readCDDBResponse(s));
}

String trackOffsetString(const TrackOffsets& offset) {
  String result(offsets.length());
  int last = offsets.size() - 1;
  for (int i = 0; i < last; ++i)
    result += (String((offsets[i] + 88200) / SAMPLES_PER_FRAME) + " ");

  result += String(offsets[last] / SAMPLES_PER_SECOND);
}

String getDiscId(Socket *s, const String& trackOffset ) {
  String req = "discid " + trackOffset;
  StringArray id = makeCDDBRequest(req);
  if (id.size() != 1)
    throw Exception("No diskid " + id.joinIntoString(", ") + " " + req);

  const String& response = id[0];
  static const char *const prefix = "200 Disc ID is ";
  if (!response.startsWith(prefix))
    throw Exception("Unexpected response " + response);

  return response.substring(strlen(prefix));
}

StringArray getPossibleCDs(Socket* sock, const String& off) {
  return makeCDDBRequest("cddb query " + getDiscId(&sock) + " " + off, sock);
}

StringArray getCDData(Socket* sock, const String& line) {
  StringArray tokens;
  tokens.addTokens(line);
  if (tokens.size() < 2)
    throw Exception("Bad CD data line " + line);

  return makeCDDBRequest("cddb read " + tokens[0] + " " + tokens[1]);
}

}  // namespace cd
}  // namespace util
}  // namespace rec
