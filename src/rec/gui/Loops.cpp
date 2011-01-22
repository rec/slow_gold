#include <algorithm>

#include "rec/gui/Loops.h"
#include "rec/util/Defaulter.h"
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
    : LoopsBase(dflt.get(desc), Address("loop_point")), length_(0) {
  fillHeader(&getHeader());
  setMultipleSelectionEnabled(true);
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
      for (int i = 0; i < proto_.selected_size(); ++i)
        proto_.set_selected(i, false);

      while (proto_.selected_size() < proto_.loop_point_size())
        proto_.add_selected(false);

      for (int i = range.getStart(); i < range.getEnd(); ++i)
        proto_.set_selected(i, true);
    }
    onChange();
  }
}

void Loops::setData(Data* d) {
  LoopsBase::setData(d);
  onChange();
}

void Loops::doSelect() {
  juce::SparseSet<int> sel;
  {
    ScopedLock l(lock_);
    for (int i = 0; i < proto_.selected_size(); ++i) {
      if (proto_.selected(i))
        sel.addRange(juce::Range<int>(i, i + 1));
    }
    if (sel == getSelectedRows())
      return;
  }
  setSelectedRows(sel, false);
}

void Loops::onChange() {
  LOG(ERROR) << "!!!";
  TableModelBase::onChange();
  // AddressListener<LoopPointList>::onChange();
  thread::callAsync(this, &Loops::doSelect);
}

bool Loops::isNewLoopPoint(double t) const {
  ScopedLock l(lock_);
  for (int i = 0; i < proto_.loop_point_size(); ++i) {
    double t2 = proto_.loop_point(i).time();
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
  if (setter_ && isNewLoopPoint(time)) {
    proto_.add_loop_point()->set_time(time);
    std::sort(proto_.mutable_loop_point()->begin(),
              proto_.mutable_loop_point()->end(),
              CompareLoopPoints());
    setter_->set(Address(), Value(proto_));
  }
}

}  // namespace gui
}  // namespace rec
