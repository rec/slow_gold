#pragma once

#include "rec/base/base.h"
#include "rec/music/Metadata.pb.h"

namespace rec {
namespace util {
namespace cd {

using TrackOffsets = juce::Array<int>;

music::Album getCachedAlbum(const VirtualFile& file, const TrackOffsets& off);

}  // namespace cd
}  // namespace util
}  // namespace rec
