#include "rec/slow/Model.h"
#include "rec/audio/source/BufferSource.h"
#include "rec/slow/Components.h"
#include "rec/audio/source/CreateSourceAndLoadMetadata.h"

namespace rec {
namespace slow {

using namespace rec::audio::util;
using namespace rec::audio::source;

Model::Model(Instance* i) : HasInstance(i),
                            fileLocker_(&lock_),
                            stretchLocker_(&lock_),
                            loopLocker_(&lock_),
                            fetchThread_(NULL) {
  persist::setter<VirtualFile>()->addListener(&fileLocker_);
}

void Model::operator()(const VirtualFile& f) {
  if (fileBuffer_.next()) {
    LOG(ERROR) << "Already reading file " << getFullDisplayName(f);
    return;
  }

  ptr<FileBuffer> buf(new FileBuffer(f));
  if (!buf->buffer_) {
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(f);
    return;
  }

  buf->thumbnail_->addListener(&components()->waveform_);
  player()->setSource(new BufferSource(*buf->buffer_->buffer()));
  fileBuffer_.setNext(buf.transfer());
  fetchThread_->notify();

  persist::Data<LoopPointList>* setter = persist::setter<LoopPointList>(f);
  components()->loops_.setData(setter);

  stretchLocker_.listenTo(persist::setter<Stretch>(f));
  loopLocker_.listenTo(setter);

  stretchLocker_.set(persist::get<Stretch>(f));
  loopLocker_.set(persist::get<LoopPointList>(f));

  components()->songData_.setFile(f);
}

}  // namespace slow
}  // namespace rec
