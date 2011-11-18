#include "rec/audio/Audio.h"
#include "rec/util/Math.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/LoopPoint.pb.h"
#include "rec/base/RealTime.h"

namespace rec {
namespace audio {

const block::BlockSet getTimeSelection(const LoopPointList& list,
                                       Samples<44100> length,
                                       double scale,
                                       bool emptyMeansAll) {
  block::BlockSet sel;
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
  for (int i = 0; i < loops.loop_point_size(); ++i) {
    RealTime t2 = loops.loop_point(i).time();
    RealTime x = t;
    RealTime y = t2;
    RealTime z = CLOSE;
    //if (util::near<RealTime>(t, t2, Loops::CLOSE))
    if (Math<RealTime>::near(x, y, z))
      return false;
  }
  return true;
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
  LoopPointList x = xx;

  for (int i = 0, j = 0; i < y.loop_point_size(); ++i) {
    double t = y.loop_point(i).time();
    if (isCloseTo(x, t)) {
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

}  // namespace audio
}  // namespace rec
