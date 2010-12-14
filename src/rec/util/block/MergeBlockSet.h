#ifndef __REC_AUDIO_SOURCE_MERGE_BLOCK_LIST_H__
#define __REC_AUDIO_SOURCE_MERGE_BLOCK_LIST_H__

#include "rec/util/block/Block.h"

namespace rec {
namespace util {
namespace block {

void merge(const Block& block, BlockSet* list);
void merge(const BlockSet& blocks, BlockSet* list);

}  // namespace block
}  // namespace util
}  // namespace rec

#endif  // __REC_AUDIO_SOURCE_MERGE_BLOCK_LIST_H__
