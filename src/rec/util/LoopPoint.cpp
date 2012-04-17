#include "rec/audio/Audio.h"
#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/util/Math.h"
#include "rec/util/LoopPoint.h"
#include "rec/base/Samples.h"

namespace rec {
namespace audio {

const block::BlockSet getTimeSelection(const LoopPointList& lpl) {
  block::BlockSet sel;
  Samples<44100> length(lpl.length());
  int size = lpl.loop_point_size();
  for (int i = 0, j; i < size; ++i) {
    for (; i < size && !lpl.loop_point(i).selected(); ++i);
    for (j = i; j < size && lpl.loop_point(j).selected(); ++j);
    if (j != i) {
      Samples<44100> begin = lpl.loop_point(i).time();
      Samples<44100> endTime = length;
      if (j < size)
        endTime = lpl.loop_point(j).time();
      Samples<44100> end = endTime;
      sel.insert(block::makeBlock(begin, end));
    }
    i = j;
  }

  if (sel.empty())
    sel.insert(block::makeBlock(0, length));

  return sel;
}

bool isCloseTo(const LoopPointList& lpl, Samples<44100> t) {
  DCHECK(lpl.has_length());
  for (int i = 0; i < lpl.loop_point_size(); ++i) {
    if (Math<Samples<44100> >::near(t, lpl.loop_point(i).time(), CLOSE_LOOPS))
      return true;
  }
  return Math<Samples<44100> >::near(t, lpl.length(), CLOSE_LOOPS);
}

LoopPointList getSelected(const LoopPointList& lpl, bool selected) {
  LoopPointList result;
  result.set_length(lpl.length());

  for (int i = 0, size = lpl.loop_point_size(); i < size; ++i) {
    if (lpl.loop_point(i).selected() == selected)
      result.add_loop_point()->CopyFrom(lpl.loop_point(i));
  }
  return result;
}

LoopPointList cutSelected(const LoopPointList& loops, bool selected) {
  LoopPointList lpl = loops;
  if (lpl.loop_point_size()) {
    bool firstWasSelected = lpl.loop_point(0).selected();
    lpl.mutable_loop_point(0)->set_selected(!selected);
    lpl = getSelected(lpl, !selected);
    lpl.mutable_loop_point(0)->set_selected(firstWasSelected);
  }
  return lpl;
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

    bool isNear = Math<Samples<44100> >::near(tx, ty, CLOSE_LOOPS);

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

void sort(LoopPointList* lpl) {
  std::sort(lpl->mutable_loop_point()->begin(),
            lpl->mutable_loop_point()->end(),
            CompareLoopPoints());
}

LoopPointList addLoopPoint(const LoopPointList& lpl, Samples<44100> t) {
  LoopPointList oneSegment;
  LoopPoint* lp = oneSegment.add_loop_point();
  lp->set_time(t);
  lp->set_selected(lpl.loop_point(getSegment(lpl, t)).selected());

  return audio::addLoopPoints(lpl, oneSegment);
}

void addLoopPointToData(const VirtualFile& file, Samples<44100> time) {
  LoopPointList lpl = data::getProto<LoopPointList>(&file);
  data::setProto(audio::addLoopPoint(lpl, time), &file);
}

int getSelectionCount(const LoopPointList& lpl) {
  int count = 0;
  for (int i = 0; i < lpl.loop_point_size(); ++i) {
    if (lpl.loop_point(i).selected())
      ++count;
  }
  return count;
}

int getSegment(const LoopPointList& lpl, Samples<44100> time) {
  int size = lpl.loop_point_size();
  for (int i = 1; ; ++i) {
    if (i >= size || time < static_cast<int64>(lpl.loop_point(i).time()))
      return i - 1;
  }
}

void toggleSelectionSegment(LoopPointList* lpl, Samples<44100> time) {
  if (!(lpl && lpl->loop_point_size())) {
    LOG(DFATAL) << "no loops";
    return;
  }
  LoopPoint* lp = lpl->mutable_loop_point(getSegment(*lpl, time));
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
