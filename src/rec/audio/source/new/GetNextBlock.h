#ifndef __REC_AUDIO_SOURCE_GET_NEXT_BLOCK_H__
#define __REC_AUDIO_SOURCE_GET_NEXT_BLOCK_H__

#include "rec/buffer/blocks.h"

namespace rec {
namespace buffer {

Block getNextBlock(const Block& requested, const BlockSet& set);

}  // namespace buffer
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_GET_NEXT_BLOCK_H__
