#include "rec/audio/Audio.h"
#include "rec/data/Data.h"
#include "rec/data/DataOps.h"
#include "rec/util/Math.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/range/Insert.h"
#include "rec/base/SampleTime.h"

namespace rec {
namespace audio {

template <typename Container>
void fillTimeSelection(Container* sel,
                       const LoopPointList& lpl,
                       bool isSelected,
                       bool allowEmpty) {
  SampleTime length(lpl.length());
  int size = lpl.loop_point_size();
  for (int i = 0, j; i < size; ++i) {
    for (; i < size && (isSelected != lpl.loop_point(i).selected()); ++i);
    for (j = i; j < size && (isSelected == lpl.loop_point(j).selected()); ++j);
    if (j != i) {
      SampleTime begin = lpl.loop_point(i).time();
      SampleTime endTime = length;
      if (j < size)
        endTime = lpl.loop_point(j).time();
      SampleTime end = endTime;
      insert(sel, SampleTimeRange(begin, end));
    }
    i = j;
  }

  if (!allowEmpty && sel->empty())
    insert(sel, SampleTimeRange(0, length));
}


const SampleTimeVector getTimeSelectionVector(const LoopPointList& lpl,
                                              bool isSelected,
                                              bool allowEmpty) {
  SampleTimeVector sel;
  fillTimeSelection(&sel, lpl, isSelected, allowEmpty);
  return sel;
}

const SampleTimeSet getTimeSelectionSet(const LoopPointList& lpl,
                                        bool isSelected,
                                        bool allowEmpty) {
  SampleTimeSet sel;
  fillTimeSelection(&sel, lpl, isSelected, allowEmpty);
  return sel;
}

const block::BlockSet getTimeSelection(const LoopPointList& lpl,
                                       bool isSelected,
                                       bool allowEmpty) {
  block::BlockSet sel;
  SampleTime length(lpl.length());
  int size = lpl.loop_point_size();
  for (int i = 0, j; i < size; ++i) {
    for (; i < size && (isSelected != lpl.loop_point(i).selected()); ++i);
    for (j = i; j < size && (isSelected == lpl.loop_point(j).selected()); ++j);
    if (j != i) {
      SampleTime begin = lpl.loop_point(i).time();
      SampleTime endTime = length;
      if (j < size)
        endTime = lpl.loop_point(j).time();
      SampleTime end = endTime;
      sel.insert(block::makeBlock(begin, end));
    }
    i = j;
  }

  if (!allowEmpty && sel.empty())
    sel.insert(block::makeBlock(0, length));

  return sel;
}

bool isCloseTo(const LoopPointList& lpl, SampleTime t) {
  DCHECK(lpl.has_length());
  SampleTime closeLoops(CLOSE_LOOPS, lpl.sample_rate());
  for (int i = 0; i < lpl.loop_point_size(); ++i) {
    if (Math<SampleTime>::near(t, lpl.loop_point(i).time(), closeLoops))
      return true;
  }
  return Math<SampleTime>::near(t, lpl.length(), closeLoops);
}

LoopPointList getSelected(const LoopPointList& lpl, bool selected) {
  LoopPointList result = lpl;
  result.mutable_loop_point()->Clear();
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
  DCHECK_EQ(x.sample_rate(), y.sample_rate());
  result.set_sample_rate(x.sample_rate());
  SampleTime closeLoops(CLOSE_LOOPS, x.sample_rate());
  uint64 length = std::max(x.length(), y.length());
  result.set_length(length);

  for (int i = 0, j = 0; ; ) {
    bool hasX = i < x.loop_point_size();
    bool hasY = j < y.loop_point_size();
    if (!(hasX || hasY))
      break;

    SampleTime tx = hasX ? x.loop_point(i).time() : length;
    SampleTime ty = hasY ? y.loop_point(j).time() : length;

    bool isNear = Math<SampleTime >::near(tx, ty, closeLoops);

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

LoopPointList addLoopPoint(const LoopPointList& lpl, SampleTime t) {
  LoopPointList oneSegment = lpl;
  oneSegment.mutable_loop_point()->Clear();

  LoopPoint* lp = oneSegment.add_loop_point();
  lp->set_time(t);
  lp->set_selected(lpl.loop_point(getSegment(lpl, t)).selected());

  return audio::addLoopPoints(lpl, oneSegment);
}

void addLoopPointToData(const VirtualFile& file, SampleTime time) {
  LoopPointList lpl = data::getProto<LoopPointList>(file);
  data::setProto(audio::addLoopPoint(lpl, time), file);
}

int getSelectionCount(const LoopPointList& lpl) {
  int count = 0;
  for (int i = 0; i < lpl.loop_point_size(); ++i) {
    if (lpl.loop_point(i).selected())
      ++count;
  }
  return count;
}

int getSegment(const LoopPointList& lpl, SampleTime time) {
  int size = lpl.loop_point_size();
  for (int i = 1; ; ++i) {
    if (i >= size || time < static_cast<int64>(lpl.loop_point(i).time()))
      return i - 1;
  }
}

void toggleSelectionSegment(LoopPointList* lpl, SampleTime time) {
  if (!(lpl && lpl->loop_point_size())) {
    LOG(DFATAL) << "no loops";
    return;
  }
  LoopPoint* lp = lpl->mutable_loop_point(getSegment(*lpl, time));
  lp->set_selected(!lp->selected());
}

Range<SampleTime > contiguousSelectionContaining(const LoopPointList& lpl,
                                                 SampleTime time) {
  int i = 1;
  int size = lpl.loop_point_size();

  for (; i < size && time >= static_cast<int64>(lpl.loop_point(i).time()); ++i);
  Range<SampleTime > range;
  if (lpl.loop_point(i - 1).selected()) {
    range.begin_ = lpl.loop_point(i - 1).time();
    bool isLast = (i == lpl.loop_point_size());
    range.end_ = isLast ? lpl.length() : lpl.loop_point(i).time();
  }
  return range;
}

}  // namespace audio
}  // namespace rec
