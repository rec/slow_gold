#ifndef __REC_AUDIO_SOURCE_GET_NEXT_BLOCK_H__
#define __REC_AUDIO_SOURCE_GET_NEXT_BLOCK_H__

#include "rec/util/block/Block.h"

namespace rec {
namespace util {
namespace block {

Block getNextBlock(const Block& requested, const BlockSet& set);

}  // namespace block
}  // namespace util
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_GET_NEXT_BLOCK_H__
