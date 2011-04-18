#include <algorithm>

#include "rec/gui/Loops.h"
#include "rec/data/yaml/Yaml.h"
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
    : TableController(dflt.get(desc), Address("loop_point"), "cut-Loops"), length_(0) {
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

bool Loops::canCopy() const {
  ScopedLock l(lock_);
  for (int i = 0; i < loopPoints_.selected_size(); ++i) {
    if (loopPoints_.selected(i))
      return true;
  }
  return false;
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

bool isNewLoopPoint(const LoopPointList& lp, RealTime t) {
  for (int i = 0; i < lp.loop_point_size(); ++i) {
    double t2 = lp.loop_point(i).time();
    if (near(t, t2))
      return false;
  }
  return true;
}

bool Loops::isNewLoopPoint(double t) const {
  ScopedLock l(lock_);
  return isNewLoopPoint(loopPoints_, t);
}

namespace {

struct CompareLoopPoints {
  bool operator()(const LoopPoint& x, const LoopPoint& y) const {
    return x.time() < y.time();
  }
};

LoopPointList getSelected(const LoopPointList& loops, bool selected) {
  LoopPointList result;

  for (int i = 0; i < loops.selected_size(); ++i) {
    if (loops.selected(i) == selected) {
      result.add_selected(selected);
      result.add_loop_point()->CopyFrom(loops.loop_point(i));
    }
  }
  return result;
}

}

string Loops::copy() const {
  ScopedLock l(lock_);
  return yaml::write(getSelected(loopPoints_, true));
}

void Loops::cut() {
  ScopedLock l(lock_);
  loopPoints_ = getSelected(loopPoints_, false);
  getData()->set(Address(), loopPoints_);
}

TimeRange Loops::selectionRange() const {
  int b = 0, size = loopPoints_.selected_size(), e;
  for (; b < size && !loopPoints_.selected(b); ++b);
  for (e = b; e < size && loopPoints_.selected(e); ++e);
  return TimeRange((b < size) ? loopPoints_.loop_point(b).time() : length_,
                   (e < size) ? loopPoints_.loop_point(e).time() : length_);
}


bool Loops::paste(const string& s) {
  LoopPointList loops;
  if (!yaml::read(s, &loops))
    return false;

  TimeRange selection = selectionRange();
  for (int i = 0; i < loops.loop_point_size(); ++i) {
    loopPoints_.add_loop_point()->CopyFrom(loops.loop_point(i));
    loopPoints_.add_selected(false);
  }

  std::sort(loopPoints_.mutable_loop_point()->begin(),
            loopPoints_.mutable_loop_point()->end(),
            CompareLoopPoints());

  for (int i = 0; i < loopPoints_.selected_size(); ++i) {
    double time = loopPoints_.loop_point(i).time();
    loopPoints_.set_selected(i, time >= selection.begin_ && time < selection.end_);
  }

  return true;
}

void Loops::addLoopPoint(double time) {
  ScopedLock l(lock_);
  if (getData() && isNewLoopPoint(time)) {
    TimeRange selection = selectionRange();

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

bool Loops::keyPressed(const juce::KeyPress& kp) {
  if (kp.getTextCharacter() == 127)
    cut();

  return true;
}

void Loops::clearSelection() {
  for (int i = 0; i < loopPoints_.selected_size(); ++i)
    loopPoints_.set_selected(i, false);

  getData()->set(Address(), loopPoints_);
}

void Loops::clearLoops() {
  loopPoints_.Clear();
  getData()->set(Address(), loopPoints_);
}

}  // namespace gui
}  // namespace rec
