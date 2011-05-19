#include <algorithm>

#include "rec/gui/audio/Loops.h"
#include "rec/data/yaml/Yaml.h"
#include "rec/data/proto/Equals.h"
#include "rec/util/Defaulter.h"
#include "rec/util/Math.h"
#include "rec/util/Range.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {
namespace audio {

static Defaulter<TableColumnList> dflt(
"column { type: TIME name: \"Time\" address { part { name: \"time\" } } } "
"column { type: STRING name: \"Name\" address { part { name: \"name\" } } } "
"column { type: STRING name: \"Notes\" address { part { name: \"notes\" } } } "
);

const double Loops::CLOSE = 0.5;

Loops::Loops(const TableColumnList* desc, bool dis)
    : length_(0),
      allowDiscontinuousSelections_(dis) {
  initialize(dflt.get(desc), Address("loop_point"), "Loops");
  fillHeader(&getHeader());
  setMultipleSelectionEnabled(true);
  loopPoints_ = new LoopPointList;
  message_.reset(loopPoints_);
}

Loops::~Loops() {}

void Loops::setLength(int len) {
  ScopedLock l(lock_);
  length_ = len;
}

void Loops::selectedRowsChanged(int lastRowSelected) {
  juce::SparseSet<int> selected;
  bool changed = false;
  {
    ScopedLock l(lock_);
    selected = getSelectedRows();
    int i = 0;
    for (; i < loopPoints_->loop_point_size(); ++i) {
      bool contains = selected.contains(i);
      if (i < loopPoints_->selected_size()) {
        if (loopPoints_->selected(i) != contains) {
          loopPoints_->set_selected(i, contains);
          changed = true;
        }
      } else {
        loopPoints_->add_selected(contains);
        changed = true;
      }
    }
  }
  if (changed)
    updatePersistentData();
}

static void print(const string& name, const juce::SparseSet<int>& ss) {
  std::cout << name;
  for (int i = 0; i < ss.size(); ++i)
    std::cout << ", " << ss[i];
  std::cout << std::endl;
}

void Loops::update() {
  juce::SparseSet<int> sel;
  {
    ScopedLock l(lock_);
    for (int i = 0; i < loopPoints_->selected_size(); ++i) {
      if (loopPoints_->selected(i))
        sel.addRange(juce::Range<int>(i, i + 1));
    }

    if (sel == getSelectedRows())
      return;
  }
  // print("update", sel);
  setSelectedRows(sel, false);

  TableController::update();
}

bool isNewLoopPointTime(const LoopPointList& lp, RealTime t) {
  for (int i = 0; i < lp.loop_point_size(); ++i) {
    RealTime t2 = lp.loop_point(i).time();
    if (near(t, t2, Loops::CLOSE))
      return false;
  }
  return true;
}

bool Loops::isNewLoopPoint(double t) const {
  ScopedLock l(lock_);
  return isNewLoopPointTime(*loopPoints_, t);
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
  return yaml::write(getSelected(*loopPoints_, true));
}

bool Loops::canCopy() const {
  ScopedLock l(lock_);
  for (int i = 0; i < loopPoints_->selected_size(); ++i) {
    if (loopPoints_->selected(i))
      return true;
  }
  return false;
}

void Loops::cut() {
  ScopedLock l(lock_);
  *loopPoints_ = getSelected(*loopPoints_, false);
 	data::set(getData(), Address(), *loopPoints_);
}

TimeRange Loops::selectionRange() const {
  int b = 0, size = loopPoints_->selected_size(), e;
  for (; b < size && !loopPoints_->selected(b); ++b);
  for (e = b; e < size && loopPoints_->selected(e); ++e);
  return TimeRange((b < size) ? loopPoints_->loop_point(b).time() : length_,
                   (e < size) ? loopPoints_->loop_point(e).time() : length_);
}

bool Loops::paste(const string& s) {
  LoopPointList loops;
  if (!yaml::read(s, &loops))
    return false;

  TimeRange selection = selectionRange();
  for (int i = 0; i < loops.loop_point_size(); ++i) {
    loopPoints_->add_loop_point()->CopyFrom(loops.loop_point(i));
    loopPoints_->add_selected(false);
  }

  std::sort(loopPoints_->mutable_loop_point()->begin(),
            loopPoints_->mutable_loop_point()->end(),
            CompareLoopPoints());

  for (int i = 0; i < loopPoints_->selected_size(); ++i) {
    double time = loopPoints_->loop_point(i).time();
    loopPoints_->set_selected(i, time >= selection.begin_ && time < selection.end_);
  }

 	data::set(getData(), Address(), *loopPoints_);
  return true;
}

void Loops::addLoopPoint(double time) {
  ScopedLock l(lock_);
  if (getData() && isNewLoopPoint(time)) {
    TimeRange selection = selectionRange();

    loopPoints_->add_loop_point()->set_time(time);
    std::sort(loopPoints_->mutable_loop_point()->begin(),
              loopPoints_->mutable_loop_point()->end(),
              CompareLoopPoints());

    loopPoints_->add_selected(false);
    for (int i = 0; i < loopPoints_->selected_size(); ++i) {
      double time = loopPoints_->loop_point(i).time();
      loopPoints_->set_selected(i, time >= selection.begin_ && time < selection.end_);
    }

    data::set(getData(), *loopPoints_);
  }
}
#if 0
bool Loops::keyPressed(const juce::KeyPress& kp) {
  if (kp.getTextCharacter() == 127)
    cut();

  return false;
}
#endif

void Loops::clearSelection() {
  for (int i = 0; i < loopPoints_->selected_size(); ++i)
    loopPoints_->set_selected(i, false);

  data::set(getData(), Address(), loopPoints_);
}

void Loops::clearLoops() {
  loopPoints_->Clear();
  data::set(getData(), Address(), loopPoints_);
}

#if 0
  if (!allowDiscontinuousSelections_) {
    if (selected.getNumRanges() > 1) {
      juce::Range<int> range = selected.getTotalRange();
      selectRangeOfRows(range.getStart(), range.getEnd());
      return;
    }
  }
#endif

}  // namespace audio
}  // namespace gui
}  // namespace rec



