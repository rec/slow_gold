#ifndef __REC_UTIL_CD_CDDBRESPONSE__
#define __REC_UTIL_CD_CDDBRESPONSE__

#include "rec/util/cd/Socket.h"
#include "rec/util/cd/Metadata.h"


namespace rec {
namespace util {
namespace cd {

bool oneCDDBResponse(String* data, StringArray* lines);
StringArray readCDDBResponse(Socket *sock);
StringArray makeCDDBRequest(const String& req, Socket *s);
String trackOffsetString(const TrackOffsets& offset);
String getDiscId(Socket *sock, const String& trackOffsets);
StringArray getPossibleCDs(Socket* sock, const String& offsets);
StringArray getCDData(Socket* sock, const String& line);

}  // namespace cd
}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CD_CDDBRESPONSE__
