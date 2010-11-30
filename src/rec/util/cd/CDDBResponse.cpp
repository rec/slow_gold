#include <algorithm>

#include <glog/logging.h>

#include "rec/util/cd/CDDBResponse.h"
#include "rec/util/Exception.h"
#include "rec/util/cd/Socket.h"
#include "rec/util/cd/StripLines.h"

using namespace juce;

namespace rec {
namespace util {
namespace cd {

bool oneCDDBResponse(String* data, StringArray* lines) {
  bool wasEmpty = (lines->size() == 0);
  if (stripLines(data, lines)) {
    if (wasEmpty) {
      const String& header = data[0];
      int status = header[0];
      if (status == '5')
        throw Exception("CDDB Error: " + string(header.toCString()));

      if (status != '2')
        throw Exception("unexpected response: " + string(header.toCString()));

      int more = header[1];
      if (more == '0')
        return false;

      if (more != '1')
        throw Exception("unexpected continuation: " + string(header.toCString()));
    }
    if ((*lines)[lines->size() - 1] == ".")
      return false;
  }
  return true;
}

StringArray readCDDBResponse(Socket *sock) {
  String data;
  StringArray lines;
  static const int TIMEOUT = 3000;
  while (readSocket(sock, &data, TIMEOUT), !oneCDDBResponse(&data, &lines));
  return lines;
}

StringArray makeCDDBRequest(const String& request, Socket *s) {
  return (writeSocket(s, request + "\n"), readCDDBResponse(s));
}

const int SAMPLES_PER_SECOND = 44100;
const int FRAMES_PER_SECOND = 75;
const int SAMPLES_PER_FRAME = 44100 / FRAMES_PER_SECOND;

String trackOffsetString(const TrackOffsets& offsets) {
  String result(offsets.size());
  for (int i = 0; i < offsets.size() - 1; ++i)
    result += (" " + String((offsets[i] + 88200) / SAMPLES_PER_FRAME));

  result += (" " + String(offsets[offsets.size() - 1] / SAMPLES_PER_SECOND));
  return result;
}

String getDiscId(Socket *s, const String& trackOffset ) {
  String req = "discid " + trackOffset;
  StringArray id = makeCDDBRequest(req, s);
  if (id.size() != 1)
    throw Exception(string("No diskid ") + id.joinIntoString(", ").toCString() + 
                    string(" ") + req.toCString()); 

  const String& response = id[0];
  static const char *const prefix = "200 Disc ID is ";
  if (!response.startsWith(prefix))
    throw Exception("Unexpected response " + string(response.toCString()));

  return response.substring(strlen(prefix));
}

StringArray getPossibleCDs(Socket* sock, const String& off) {
  return makeCDDBRequest("cddb query " + getDiscId(sock, off) + " " + off, sock);
}

StringArray getCDData(Socket* sock, const String& line) {
  StringArray tokens;
  tokens.addTokens(line, true);
  if (tokens.size() < 2)
    throw Exception(string("Bad CD data line ") + line.toCString());

  return makeCDDBRequest("cddb read " + tokens[0] + " " + tokens[1], sock);
}

}  // namespace cd
}  // namespace util
}  // namespace rec
