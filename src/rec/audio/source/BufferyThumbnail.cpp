#include "rec/audio/source/BufferyThumbnail.h"
#include "rec/audio/source/TrackSource.h"
#include "rec/widget/tree/VolumeFile.h"
#include "rec/util/thread/FileWriter.h"
#include "rec/util/thread/Trash.h"

using namespace rec::widget::tree;

namespace rec {
namespace audio {
namespace source {

BufferyThumbnail::BufferyThumbnail(const VolumeFile& f, int blockSize)
  : Buffery(Snoopy::add(createSource(f), this), blockSize),
    file_(getShadowFile(f, "thumbnail.stream")) {
}

void BufferyThumbnail::operator()(const AudioSourceChannelInfo& i) {
}

BufferyThumbnail::~BufferyThumbnail() {}

}  // namespace source
}  // namespace audio
}  // namespace rec
