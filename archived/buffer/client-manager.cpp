#include <algorithm>

#include "rec/buffer/client-manager.h"

namespace rec {
namespace buffer {

ClientId ClientManager::newClient() {
  ClientId client(clients_.size() ? (1 + clients_.rbegin()->first) : 0);
  clients_.insert(std::make_pair(client, 0));
  return client;
}

void ClientManager::freeClient(ClientId client) {
  clients_.erase(client);
  OffsetsList::iterator i;
  for (i = offsetsList_.begin(); i != offsetsList_.end(); ++i)
    i->erase(client);
}

void ClientManager::addBlocks(const BlockList& blocks) {
  queue_.insert(queue_.end(), blocks.begin(), blocks.end());
  offsetsList_.resize(queue_.size(), clients_);
}

BlockList ClientManager::erase(ClientId client, Size begin) {
  BlockList blocks;
  BlockList::iterator i;
  for (i = queue_.begin(); i != queue_.end() && i->first != begin; ++i) {}

  if (i != queue_.end()) {
    OffsetsList::iterator offsets = offsetsList_.begin() + (i - queue_.begin());
    Offsets::iterator o = offsets->find(client);
    if (o != offsets->end() && o->second >= getSize(*i))
      offsets->erase(client);
  }

  return clean();
}

BlockList ClientManager::clean() {
  OffsetsList::iterator oBegin = offsetsList_.begin();
  OffsetsList::iterator i = oBegin;
  for (; i != offsetsList_.end() && !i->size(); ++i) { }

  BlockList::iterator qBegin = queue_.begin();
  BlockList::iterator qEnd = qBegin + (i - oBegin);
  BlockList blocks(qBegin, qEnd);
  queue_.erase(qBegin, qEnd);
  offsetsList_.erase(oBegin, i);

  return blocks;
}

Size ClientManager::getBlocks(ClientId client, Size size, BlockList* blocks) {
  Size copied = 0;
  for (BlockList::iterator i = queue_.begin();
       i != queue_.end() && size > copied; ++i) {
    Offsets& offsets = offsetsList_[i - queue_.begin()];

    if (offsets.find(client) != offsets.end()) {
      Size offset = offsets[client];
      Size blockSize = std::min(getSize(*i) - offset, size - copied);

      if (blockSize > 0) {
        offsets[client] = offset + blockSize;
        Size begin = i->first + offset;
        blocks->push_back(std::make_pair(begin, begin + blockSize));
        copied += blockSize;
      }
    }
  }
  return copied;
}

}  // namespace buffer
}  // namespace rec
