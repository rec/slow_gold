#include "rec/audio/Audio.h"
#include "rec/data/Data.h"
#include "rec/util/Math.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/LoopPoint.pb.h"
#include "rec/base/Samples.h"

namespace rec {
namespace audio {

const block::BlockSet getTimeSelection(const LoopPointList& list) {
  block::BlockSet sel;
  Samples<44100> length(list.length());
  int size = list.loop_point_size();
  for (int i = 0, j; i < size; ++i) {
    for (; i < size && !list.loop_point(i).selected(); ++i);
    for (j = i; j < size && list.loop_point(j).selected(); ++j);
    if (j != i) {
      Samples<44100> begin = list.loop_point(i).time();
      Samples<44100> endTime = length;
      if (j < size)
        endTime = list.loop_point(j).time();
      Samples<44100> end = endTime;
      sel.insert(block::makeBlock(Samples<44100>(begin), Samples<44100>(end)));
    }
    i = j;
  }

  return sel;
}

static const Samples<44100> CLOSE = 44100 / 2;

bool isCloseTo(const LoopPointList& loops, Samples<44100> t) {
  DCHECK(loops.has_length());
  for (int i = 0; i < loops.loop_point_size(); ++i) {
    Samples<44100> z = CLOSE;
    if (Math<Samples<44100> >::near(t, loops.loop_point(i).time(), CLOSE))
      return true;
  }
  return Math<Samples<44100> >::near(t, loops.length(), CLOSE);
}

LoopPointList getSelected(const LoopPointList& loops, bool selected) {
  LoopPointList result;
  result.set_length(loops.length());

  for (int i = 0, size = loops.loop_point_size(); i < size; ++i) {
    if (loops.loop_point(i).selected() == selected)
      result.add_loop_point()->CopyFrom(loops.loop_point(i));
  }
  return result;
}

LoopPointList addLoopPoints(const LoopPointList& x, const LoopPointList& y) {
  LoopPointList result;
  uint64 length = std::max(x.length(), y.length());
  result.set_length(length);

  for (int i = 0, j = 0; ; ) {
    bool hasX = i < x.loop_point_size();
    bool hasY = j < y.loop_point_size();
    if (!(hasX || hasY))
      break;

    Samples<44100> tx = hasX ? x.loop_point(i).time() : length;
    Samples<44100> ty = hasY ? y.loop_point(j).time() : length;

    bool isNear = Math<Samples<44100> >::near(tx, ty, CLOSE);

    bool useX = (!hasY || isNear || tx < ty);
    const LoopPoint& lp = useX ? x.loop_point(i++) : y.loop_point(j++);
    result.add_loop_point()->CopyFrom(lp);
    if (isNear)  // Remove dupes.
      j++;
  }

  return result;
}

namespace {

struct CompareLoopPoints {
  bool operator()(const LoopPoint& x, const LoopPoint& y) const {
    return x.time() < y.time();
  }
};

}  // namespace

void sort(LoopPointList* loops) {
  std::sort(loops->mutable_loop_point()->begin(),
            loops->mutable_loop_point()->end(),
            CompareLoopPoints());
}

LoopPointList addLoopPoint(const LoopPointList& lpl, Samples<44100> t) {
  LoopPointList oneSegment;
  LoopPoint* lp = oneSegment.add_loop_point();
  lp->set_time(t);
  lp->set_selected(lpl.loop_point(getSegment(lpl, t)).selected());

  return audio::addLoopPoints(lpl, oneSegment);
}

void addLoopPointToEditable(const VirtualFile& file, Samples<44100> time) {
  LoopPointList loops = data::get<LoopPointList>(file);
  data::set(audio::addLoopPoint(loops, time), file);
}

int getSelectionCount(const LoopPointList& loops) {
  int count = 0;
  for (int i = 0; i < loops.loop_point_size(); ++i) {
    if (loops.loop_point(i).selected())
      ++count;
  }
  return count;
}

int getSegment(const LoopPointList& loops, Samples<44100> time) {
  int size = loops.loop_point_size();
  for (int i = 1; ; ++i) {
    if (i >= size || time < static_cast<int64>(loops.loop_point(i).time()))
      return i - 1;
  }
}

void toggleSelectionSegment(LoopPointList* loops, Samples<44100> time) {
  if (!(loops && loops->loop_point_size())) {
    LOG(DFATAL) << "no loops";
    return;
  }
  LoopPoint* lp = loops->mutable_loop_point(getSegment(*loops, time));
  lp->set_selected(!lp->selected());
}

Range<Samples<44100> > contiguousSelectionContaining(const LoopPointList& lpl,
                                              Samples<44100> time) {
  int i = 1;
  int size = lpl.loop_point_size();

  for (; i < size && time >= static_cast<int64>(lpl.loop_point(i).time()); ++i);
  Range<Samples<44100> > range;
  if (lpl.loop_point(i - 1).selected()) {
    range.begin_ = lpl.loop_point(i - 1).time();
    bool isLast = (i == lpl.loop_point_size());
    range.end_ = isLast ? lpl.length() : lpl.loop_point(i).time();
  }
  return range;
}


}  // namespace audio
}  // namespace rec
