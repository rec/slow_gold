#ifndef __REC_AUDIO_SOURCE_GET_NEXT_BLOCK_H__
#define __REC_AUDIO_SOURCE_GET_NEXT_BLOCK_H__

#include "rec/util/block/Block.h"

namespace rec {
namespace util {
namespace block {

BlockSet difference(const Block& block, const BlockSet& set);
BlockSet difference(const BlockSet& set, const BlockSet& set2);

Block firstEmptyBlockAfter(const BlockSet& s, int pos, int length);

}  // namespace block
}  // namespace util
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_GET_NEXT_BLOCK_H__
