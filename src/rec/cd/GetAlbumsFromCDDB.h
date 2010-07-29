#ifndef __REC_CD_GETALBUMSFROMCDDB__
#define __REC_CD_GETALBUMSFROMCDDB__

#include "juce_amalgamated.h"

namespace rec {
namespace cd {

struct Track {
  int length_;
  int frameOffset_;

  String title_;
  String artist_;
  String extdata_;
};

struct Album {
  int discid_;
  int length_;
  int revision_;
  int year_;

  String category_;
  String genre_;
  String title_;
  String artist_;
  String extdata_;

  Array<Track> tracks_;
};

// Fill a list of albums from the CDDB.  Return an error message or the empty
// string if there was no error.
String getAlbumsFromCDDB(const Array<int>& trackOffsets, Array<Album>* albums);

}  // namespace cd
}  // namespace rec

#endif  // __REC_CD_GETALBUMSFROMCDDB__
