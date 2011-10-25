#include "rec/slow/Model.h"
#include "rec/audio/Audio.h"
#include "rec/audio/source/FrameSource.h"
#include "rec/audio/source/Empty.h"
#include "rec/audio/source/Selection.h"
#include "rec/audio/util/Frame.h"
#include "rec/data/persist/TypedEditable.h"
#include "rec/data/Data.h"
#include "rec/music/CreateMusicFileReader.h"
#include "rec/util/LoopPoint.h"
#include "rec/slow/Components.h"
#include "rec/slow/Threads.h"
#include "rec/util/block/Difference.h"
#include "rec/util/block/FillSeries.h"
#include "rec/widget/waveform/Cursor.h"
#include "rec/widget/waveform/Zoom.h"

namespace rec {
namespace slow {

using namespace rec::audio::util;
using namespace rec::audio::source;
using namespace rec::gui::audio;
using namespace rec::music;
using namespace rec::util::block;
using namespace rec::widget::waveform;

namespace {

const int PARAMETER_WAIT = 1000;
const int PRELOAD = 10000;

class LoopListenerImpl : public DataListener<LoopPointList> {
 public:
  explicit LoopListenerImpl(Model* model) : model_(model) {}
  virtual void onDataChange(const LoopPointList& p) {
    model_->setLoopPointList(p);
  }

 private:
  Model* const model_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(LoopListenerImpl);
};

void doSetCursorTime(Model* model, int index, RealTime time,
                     const VirtualFile& f) {
  if (index < 0) {
    model->jumpToTime(time);
  } else {
    LoopPointList loops(data::get<LoopPointList>(f));
    loops.mutable_loop_point(index)->set_time(time);
    data::set(loops, f);
  }
}

void dropFiles(Instance* instance, const gui::DropFiles& dropFiles) {
  const file::VirtualFileList& files = dropFiles.files_;
  if (dropFiles.target_ == &instance->components_->waveform_) {
    if (files.file_size() >= 1)
      instance->model_->setFile(files.file(0));

    LOG_IF(ERROR, files.file_size() != 1);

  } else if (dropFiles.target_ == instance->components_->directoryTree_.treeView()) {
    using file::getFile;

    typedef std::set<string> FileSet;
    FileSet existing;
    VirtualFileList list(data::get<file::VirtualFileList>());
    for (int i = 0; i < list.file_size(); ++i)
      existing.insert(str(getFile(list.file(i)).getFullPathName()));

    for (int i = 0; i < files.file_size(); ++i) {
      if (existing.find(str(getFile(files.file(i)).getFullPathName())) == existing.end())
        data::editable<file::VirtualFileList>()->append(files.file(i), data::Address("file"));
    }
  }
}

void setInstanceFile(Instance* instance, const VirtualFile& f,
                     const VirtualFile& oldFile) {
  instance->player_->clear();
  Components* components = instance->components_.get();
  ThumbnailBuffer* thumbnailBuffer = instance->model_->thumbnailBuffer();

  components->playerController_.clearLevels();
  components->directoryTree_.refreshNode(oldFile);

  bool isEmpty = file::empty(f);
  components->waveform_.setEmpty(isEmpty);

  instance->model_->setFileVariable(f);
  components->directoryTree_.refreshNode(f);
  data::set(f);

  if (isEmpty)
    return;

  if (!thumbnailBuffer->setReader(f, music::createMusicFileReader(f))) {
    LOG(ERROR) << "Unable to read file " << getFullDisplayName(f);
    return;
  }

  LoopPointList loopPointList = data::get<LoopPointList>(f);
  if (!loopPointList.loop_point_size()) {
    loopPointList.add_loop_point()->set_selected(true);
    RealTime time = Samples<44100>(thumbnailBuffer->buffer()->length());
    loopPointList.add_loop_point()->set_time(time);
  }
  data::set(loopPointList, f);

  instance->threads_->fillThread()->notify();
}

void jumpToTimeSelection(Model* model, const block::BlockSet& ts,
                         Samples<44100> time) {
  if (!ts.empty()) {
    BlockSet::const_iterator i = ts.begin();
    for (; i != ts.end(); ++i) {
      if (time < i->second) {
        if (time < i->first)
          model->jumpToTime(i->first);
        return;
      }
    }
    model->jumpToTime(ts.begin()->first);
  }
}

}

Model::Model(Instance* i) : HasInstance(i),
                            time_(0),
                            triggerPosition_(-1),
                            updateBuffer_(2, 1024),
                            updateSource_(thumbnailBuffer_.buffer()->frames()),
                            loopListener_(new LoopListenerImpl(this)) {
  audio::Source *s = new FrameSource<short, 2>(thumbnailBuffer_.buffer()->frames());
  player()->setSource(s);
  player()->timeBroadcaster()->addListener(this);
  components()->waveform_.setAudioThumbnail(thumbnailBuffer_.thumbnail());
  updateInfo_.buffer = &updateBuffer_;
  updateInfo_.startSample = 0;
}


void Model::operator()(const gui::DropFiles& df) {
  dropFiles(instance_, df);
}

void Model::setFile(const VirtualFile& f) {
  VirtualFile old = file_;
  file_ = f;
  setInstanceFile(instance_, file_, old);
}

thread::Result Model::fillOnce() {
  FillableFrameBuffer<short, 2>* buffer = thumbnailBuffer_.buffer();
  if (buffer && buffer->isFull()) {
    thumbnailBuffer_.writeThumbnail();
    return static_cast<thread::Result>(PARAMETER_WAIT);
  }

  bool empty = false;
  if (triggerPosition_ == -1) {
    // Find the first moment in the selection after "time" that needs to be filled.
    BlockSet fill = difference(timeSelection_, buffer->filled());
    if (!fill.empty()) {
      BlockList fillList = fillSeries(fill, time_, player()->length());
      if (!fillList.empty())
        buffer->setNextFillPosition(fillList.begin()->first);
      else
        empty = true;

    } else {
      empty = true;
    }
  }

  if (triggerPosition_ != -1 &&
      buffer->hasFilled(block::Block(triggerPosition_,
                                     triggerPosition_ + PRELOAD))) {
    jumpToTime(triggerPosition_);
  }

  int64 pos = buffer->position();
  int filled = static_cast<int>(buffer->fillNextBlock());
  DCHECK(filled);

  updateInfo_.numSamples = filled;
  updateBuffer_.setSize(2, filled, false, false, true);
  updateSource_.setNextReadPosition(pos);
  updateSource_.getNextAudioBlock(updateInfo_);
  thumbnailBuffer_.addBlock(pos, updateInfo_);

  thread::callAsync(&components()->waveform_, &Waveform::repaint);
  return thread::YIELD;
}

void Model::zoom(RealTime time, double k) {
  widget::waveform::zoom(file_, player()->length(), time, k);
}

void Model::jumpToTime(Samples<44100> pos) {
  {
    ScopedLock l(lock_);
    if (!block::contains(timeSelection_, pos)) {
      // TODO: fix this.
      LOG(ERROR) << "Tried to jump to position outside selection " << pos;
      return;
    }

    FillableFrameBuffer<short, 2>* buffer = thumbnailBuffer_.buffer();
    triggerPosition_ = pos;
    if (buffer && !buffer->hasFilled(block::Block(pos, pos + PRELOAD))) {
      buffer->setNextFillPosition(pos);
      if (player()->state())
        return;
    }
    triggerPosition_ = -1;
  }

	player()->setNextReadPosition(pos);
}

void Model::setLoopPointList(const LoopPointList& loops) {
  if (!empty()) {
    timeSelection_ = audio::getTimeSelection(loops);
    jumpToTimeSelection(this, timeSelection_, time_);
  }
}

void Model::setCursorTime(int index, RealTime time) {
  doSetCursorTime(this, index, time, file_);
}

}  // namespace slow
}  // namespace rec
