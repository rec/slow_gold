#include <algorithm>

#include "rec/gui/Loops.h"
#include "rec/util/Defaulter.h"
#include "rec/util/Range.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

static Defaulter<TableColumnList> dflt(
"column { type: TIME name: \"Time\" address { field { name: \"time\" } } } "
"column { type: STRING name: \"Name\" address { field { name: \"name\" } } } "
"column { type: STRING name: \"Notes\" address { field { name: \"notes\" } } } "
);

const double Loops::CLOSE = 0.5;

Loops::Loops(const TableColumnList* desc)
    : TableController(dflt.get(desc), Address("loop_point")), length_(0) {
  fillHeader(&getHeader());
  setMultipleSelectionEnabled(true);
  message_.reset(&loopPoints_);
}

Loops::~Loops() {
  message_.transfer();
}

void Loops::setLength(int len) {
  ScopedLock l(lock_);
  length_ = len;
}

void Loops::selectedRowsChanged(int lastRowSelected) {
  juce::Range<int> range;
  int numRanges;
  {
    ScopedLock l(lock_);
    const juce::SparseSet<int> selected = getSelectedRows();

    range = selected.getTotalRange();
    numRanges = selected.getNumRanges();
  }

  if (numRanges > 1) {
    selectRangeOfRows(range.getStart(), range.getEnd());

  } else {
    {
      ScopedLock l(lock_);
      for (int i = 0; i < loopPoints_.selected_size(); ++i)
        loopPoints_.set_selected(i, false);

      while (loopPoints_.selected_size() < loopPoints_.loop_point_size())
        loopPoints_.add_selected(false);

      for (int i = range.getStart(); i < range.getEnd(); ++i)
        loopPoints_.set_selected(i, true);
    }
    updatePersistentData();
  }
}

static void print(const string& name, const juce::SparseSet<int>& ss) {
  std::cout << name;
  for (int i = 0; i < ss.size(); ++i)
    std::cout << ", " << ss[i];
  std::cout << std::endl;
}

void Loops::doSelect() {
  juce::SparseSet<int> sel;
  {
    ScopedLock l(lock_);
    for (int i = 0; i < loopPoints_.selected_size(); ++i) {
      if (loopPoints_.selected(i))
        sel.addRange(juce::Range<int>(i, i + 1));
    }

    if (sel == getSelectedRows())
      return;
  }
  setSelectedRows(sel, false);
}

void Loops::onDataChange() {
  getData()->fill(&loopPoints_);
  TableController::onDataChange();
  thread::callAsync(this, &Loops::doSelect);
}

bool Loops::isNewLoopPoint(double t) const {
  ScopedLock l(lock_);
  for (int i = 0; i < loopPoints_.loop_point_size(); ++i) {
    double t2 = loopPoints_.loop_point(i).time();
    if (near(t, t2) || near(t + length_, t2) || near(t, t2 + length_))
      return false;
  }
  return true;
}

namespace {

struct CompareLoopPoints {
  bool operator()(const LoopPoint& x, const LoopPoint& y) const {
    return x.time() < y.time();
  }
};

}

void Loops::addLoopPoint(double time) {
  ScopedLock l(lock_);
  if (getData() && isNewLoopPoint(time)) {
    int begin = 0, size = loopPoints_.selected_size(), end;
    for (; begin < size && !loopPoints_.selected(begin); ++begin);
    for (end = begin; end < size && loopPoints_.selected(end); ++end);
    TimeRange selection((begin < size) ? loopPoints_.loop_point(begin).time() : length_,
						(end < size) ? loopPoints_.loop_point(end).time() : length_);

    loopPoints_.add_loop_point()->set_time(time);
    std::sort(loopPoints_.mutable_loop_point()->begin(),
              loopPoints_.mutable_loop_point()->end(),
              CompareLoopPoints());

    loopPoints_.add_selected(false);
    for (int i = 0; i < loopPoints_.selected_size(); ++i) {
      double time = loopPoints_.loop_point(i).time();
      loopPoints_.set_selected(i, time >= selection.begin_ && time < selection.end_);
    }

    getData()->set(Address(), loopPoints_);
  }
}

}  // namespace gui
}  // namespace rec
