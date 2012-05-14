#ifndef __REC_MUSIC_CREATEMUSICFILEREADER__
#define __REC_MUSIC_CREATEMUSICFILEREADER__

#include "rec/base/Trans.h"

namespace rec {
namespace music {

class Metadata;

class MusicFileReader {
 public:
  MusicFileReader(const VirtualFile&);
  AudioFormatReader* reader() { return reader_.get(); }
  const String& errorTitle() const { return errorTitle_; }
  const String& errorDetails() const { return errorDetails_; }
  AudioFormatReader* transfer() { return reader_.transfer(); }
  bool empty() const { return !reader_; }

  void setError(const String& title, const String& details) {
    errorTitle_ = title;
    errorDetails_ = details;
  }

  static void translateAll();

 private:
  ptr<AudioFormatReader> reader_;
  String errorTitle_;
  String errorDetails_;
};

extern Trans FILE_TOO_SMALL;
extern Trans FILE_TOO_SMALL_FULL;

}  // namespace music
}  // namespace rec

#endif  // __REC_MUSIC_CREATEMUSICFILEREADER__
