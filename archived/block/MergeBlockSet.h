#ifndef __REC_AUDIO_SOURCE_MERGE_BLOCK_LIST_H__
#define __REC_AUDIO_SOURCE_MERGE_BLOCK_LIST_H__

#include "rec/block/blocks.h"

namespace rec {
namespace buffer {

void merge(const Block& block, BlockSet* list);

}  // namespace buffer
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_MERGE_BLOCK_LIST_H__
