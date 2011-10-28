#include <algorithm>

#include "rec/base/RealTime.h"
#include "rec/data/yaml/Yaml.h"
#include "rec/data/proto/Equals.h"
#include "rec/data/Value.h"
#include "rec/gui/audio/Loops.h"
#include "rec/util/Defaulter.h"
#include "rec/util/Math.h"
#include "rec/util/Range.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {
namespace audio {

static Def<TableColumnList> dflt(
"column { type: TIME name: \"Time\" address { part { name: \"time\" } } } "
#if 0
"column { type: STRING name: \"Name\" address { part { name: \"name\" } } } "
"column { type: STRING name: \"Notes\" address { part { name: \"notes\" } } } "
#endif
);

class LoopPointDataListener : public DataListener<LoopPointList> {
 public:
  explicit LoopPointDataListener(Loops* loops) : loops_(loops) {}

  virtual void onDataChange(const LoopPointList& p) {
  	MessageManagerLock l;
    loops_->setLoopPoints(p);
  }

  virtual void setData(data::TypedEditable<LoopPointList>* d) {
    DataListener<LoopPointList>::setData(d);
    loops_->setUntypedEditable(d);
  }

 private:
  Loops* loops_;

  DISALLOW_COPY_AND_ASSIGN(LoopPointDataListener);
};

const double Loops::CLOSE = 0.5;

Loops::Loops(ApplicationCommandManager* manager,
             const TableColumnList* desc)
    : component::Focusable<TableController>(manager),
      length_(0),
      dataListener_(new LoopPointDataListener(this)) {
  initialize(dflt.get(desc), data::Address("loop_point"), "Loops");
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
  bool changed = false;
  {
    ScopedLock l(lock_);
    juce::SparseSet<int> selected(getSelectedRows());
    for (int i = 0; i < loopPoints_->loop_point_size(); ++i) {
      LoopPoint* lp = loopPoints_->mutable_loop_point(i);
      bool contains = selected.contains(i);
      if (lp->selected() != contains) {
          lp->set_selected(contains);
          changed = true;
      }
    }
  }
  if (changed)
    updatePersistentData();
}

void Loops::update() {
  bool selectionChanged;
  juce::SparseSet<int> sel;
  {
    ScopedLock l(lock_);
    for (int i = 0; i < loopPoints_->loop_point_size(); ++i) {
      if (loopPoints_->loop_point(i).selected())
        sel.addRange(juce::Range<int>(i, i + 1));
    }

    selectionChanged = (sel != getSelectedRows());
  }
  if (selectionChanged)
    setSelectedRows(sel, false);

  TableController::update();
}

bool isNewLoopPointTime(const LoopPointList& lp, RealTime t) {
  for (int i = 0; i < lp.loop_point_size(); ++i) {
    RealTime t2 = lp.loop_point(i).time();
    if (near<double>(t, t2, Loops::CLOSE))
      return false;
  }
  return true;
}

bool Loops::isNewLoopPoint(RealTime t) const {
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

  for (int i = 0, size = loops.loop_point_size(); i < size; ++i) {
    if (loops.loop_point(i).selected() == selected || i == size - 1)
      result.add_loop_point()->CopyFrom(loops.loop_point(i));
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
  return getSelected(*loopPoints_, true).loop_point_size();
}

void Loops::cut() {
  ScopedLock l(lock_);
  *loopPoints_ = getSelected(*loopPoints_, false);
 	getUntypedEditable()->set(*loopPoints_);
}

Range<RealTime> Loops::selectionRange() const {
  int b = 0, size = loopPoints_->loop_point_size() - 1, e;
  DCHECK_GT(size, 0);
  for (; b < size && !loopPoints_->loop_point(b).selected(); ++b);
  for (e = b; e < size && loopPoints_->loop_point(e).selected(); ++e);
  return Range<RealTime>(loopPoints_->loop_point(b).time(),
                         loopPoints_->loop_point(e).time());
}

void Loops::addLoopPoints(const LoopPointList& loops) {
  ScopedLock l(lock_);
  Range<RealTime> selection = selectionRange();
  for (int i = 0; i < loops.loop_point_size(); ++i) {
    if (isNewLoopPoint(loops.loop_point(i).time()))
      loopPoints_->add_loop_point()->CopyFrom(loops.loop_point(i));
  }

  std::sort(loopPoints_->mutable_loop_point()->begin(),
            loopPoints_->mutable_loop_point()->end(),
            CompareLoopPoints());

  for (int i = 0; i < loopPoints_->loop_point_size() - 1; ++i) {
    double time = loopPoints_->loop_point(i).time();
    loopPoints_->mutable_loop_point(i)->set_selected(time >= selection.begin_ &&
                                                     time < selection.end_);
  }

 	getUntypedEditable()->set(*loopPoints_, data::Address());
  updateAndRepaint();
}

bool Loops::paste(const string& s) {
  LoopPointList loops;
  if (yaml::read(s, &loops)) {
    addLoopPoints(loops);
    return true;
  }
  return false;
}

void Loops::addLoopPoint(RealTime time) {
  LoopPointList loops;
  loops.add_loop_point()->set_time(time);
  addLoopPoints(loops);
}


#if 0
static void print(const string& name, const juce::SparseSet<int>& ss) {
  std::cout << name;
  for (int i = 0; i < ss.size(); ++i)
    std::cout << ", " << ss[i];
  std::cout << std::endl;
}
#endif

}  // namespace audio
}  // namespace gui
}  // namespace rec



