#include "rec/audio/Audio.h"
#include "rec/data/Data.h"
#include "rec/util/Math.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/LoopPoint.pb.h"
#include "rec/base/RealTime.h"

namespace rec {
namespace audio {

const block::BlockSet getTimeSelection(const LoopPointList& list,
                                       double scale,
                                       bool emptyMeansAll) {
  block::BlockSet sel;
  DCHECK(list.has_length());
  RealTime length(list.length());
  int size = list.loop_point_size();
  if (size > 0) {
    for (int i = 0, j; i < size; ++i) {
      for (; i < size && !list.loop_point(i).selected(); ++i);
      for (j = i; j < size && list.loop_point(j).selected(); ++j);
      if (j != i) {
        RealTime begin = scale * list.loop_point(i).time();
        RealTime endTime = length;
        if (j < size)
        	endTime = list.loop_point(j).time();
        RealTime end = scale * endTime;
        sel.insert(block::makeBlock(Samples<44100>(begin), Samples<44100>(end)));
      }
      i = j;
    }
  }
  if (emptyMeansAll && sel.empty())
    sel.insert(block::makeBlock(0, Samples<44100>(length)));
  return sel;
}

static const RealTime CLOSE = 0.5;

bool isCloseTo(const LoopPointList& loops, RealTime t) {
  DCHECK(loops.has_length());
  for (int i = 0; i < loops.loop_point_size(); ++i) {
    RealTime z = CLOSE;
    if (Math<RealTime>::near(t, loops.loop_point(i).time(), CLOSE))
      return true;
  }
  return Math<RealTime>::near(t, loops.length(), CLOSE);
}

LoopPointList getSelected(const LoopPointList& loops, bool selected) {
  LoopPointList result;

  for (int i = 0, size = loops.loop_point_size(); i < size; ++i) {
    if (loops.loop_point(i).selected() == selected || i == size - 1)
      result.add_loop_point()->CopyFrom(loops.loop_point(i));
  }
  return result;
}

LoopPointList addLoopPoints(const LoopPointList& xx, const LoopPointList& y) {
  DCHECK(xx.has_length());
  LoopPointList x = xx;

  for (int i = 0, j = 0; i < y.loop_point_size(); ++i) {
    double t = y.loop_point(i).time();
    if (!isCloseTo(x, t)) {
      LoopPoint* lp = x.add_loop_point();
      lp->CopyFrom(y.loop_point(i));
      for (; j < x.loop_point_size() && x.loop_point(j).time() <= t; ++j);
    }
  }

  sort(&x);
  return x;
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

LoopPointList addLoopPoint(const LoopPointList& lp, RealTime t) {
  LoopPointList oneSegment;
  oneSegment.add_loop_point()->set_time(t);
  return audio::addLoopPoints(lp, oneSegment);
}

void addLoopPointToEditable(const VirtualFile& file, RealTime time) {
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

int getSegment(const LoopPointList& loops, RealTime time) {
  for (int i = 1; i < loops.loop_point_size(); ++i) {
    if (time < loops.loop_point(i).time())
      return i - 1;
  }
  return 0;
}

void toggleSelectionSegment(LoopPointList* loops, RealTime time) {
  LoopPoint* lp = loops->mutable_loop_point(getSegment(*loops, time));
  lp->set_selected(!lp->selected());
}


}  // namespace audio
}  // namespace rec
