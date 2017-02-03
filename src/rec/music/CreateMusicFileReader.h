#pragma once

#include "rec/base/Trans.h"

TRAN_EXTERNAL(FILE_TOO_SMALL);
TRAN_EXTERNAL(FILE_TOO_SMALL_FULL);

namespace rec {
namespace music {

class Metadata;

class MusicFileReader {
  public:
    MusicFileReader(const VirtualFile&);
    AudioFormatReader* reader() { return reader_.get(); }
    const String& errorTitle() const { return errorTitle_; }
    const String& errorDetails() const { return errorDetails_; }
    AudioFormatReader* release() { return reader_.release(); }
    bool empty() const { return !reader_; }

    void setError(const String& title, const String& details) {
        errorTitle_ = title;
        errorDetails_ = details;
    }

  private:
    std::unique_ptr<AudioFormatReader> reader_;
    String errorTitle_;
    String errorDetails_;
};

}  // namespace music
}  // namespace rec
