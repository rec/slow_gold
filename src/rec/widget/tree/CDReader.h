#ifndef __REC_WIDGET_TREE_CDREADER__
#define __REC_WIDGET_TREE_CDREADER__

#include "rec/base/base.h"

namespace rec {
namespace widget {
namespace tree {

AudioCDReader* getCDReader(const string& idString);
int getAudioTrackIndex(const AudioCDReader& reader, int track);
AudioFormatReader* createCDTrackReader(const string& idString, int track);
int getAudioTrackCount(const AudioCDReader& reader);

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_CDREADER__
