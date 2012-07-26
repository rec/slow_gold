#ifndef __REC_AUDIO_SOURCE_GET_NEXT_BLOCK_H__
#define __REC_AUDIO_SOURCE_GET_NEXT_BLOCK_H__

#include "rec/util/block/Block.h"

namespace rec {
namespace util {
namespace block {

BlockSet difference(const Block&, const BlockSet&);
BlockSet difference(const BlockSet&, const BlockSet&);
BlockSet symmetricDifference(const BlockSet&, const BlockSet&);

Block firstEmptyBlockAfter(const BlockSet& s, int64 pos, int64 length);

}  // namespace block
}  // namespace util
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_GET_NEXT_BLOCK_H__
