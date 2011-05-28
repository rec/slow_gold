#include "rec/slow/Selections.h"
#include "rec/slow/Instance.h"
#include "rec/slow/Model.h"
#include "rec/util/LoopPoint.pb.h"

namespace rec {
namespace slow {

namespace {

template <typename Operator>
void apply(Operator op, Instance* i) {
  LoopPointList loops(i->model_->loopPointList());
  (*op)(&loops);
  persist::set(loops, i->model_->file());
}

template <typename Operator>
void applyEach(Operator op, LoopPointList* loops) {
  for (int i = 0; i < loops->loop_point_size(); ++i) {
    LoopPoint* lp = loops->mutable_loop_point(i);
    lp->set_selected((*op)(lp->selected(), i));
  }
}

bool selectAll1(bool, int) { return true; }
void selectAll2(LoopPointList* lpl) { applyEach(&selectAll1, lpl); }

bool selectNone1(bool, int) { return false; }
void selectNone2(LoopPointList* lpl) { applyEach(&selectNone1, lpl); }

bool selectInvert1(bool s, int) { return !s; }
void selectInvert2(LoopPointList* lpl) { applyEach(&selectInvert1, lpl); }

enum Setting {SET, RESET, TOGGLE, ONLY};

struct Selecter {
  Selecter(int index, Setting s = SET) : index_(index), setting_(s) {}

  bool operator()(bool selected, int i) const {
    if (i != index_)
      return selected && (setting_ != ONLY);
    if (setting_ == TOGGLE)
      return !selected;
    return (setting_ != RESET);
  }

  void operator()(LoopPointList* lpl) const {
    applyEach(this, lpl);
  }

  void set(Instance* i) const {
    apply(this, i);
  }

  int index_;
  Setting setting_;
};

Range<int> getSelection(const LoopPointList& lpl) {
  Range<int> sel;
  int size = lpl.loop_point_size();
  for (int i = 0; i < size; ++i) {
    if (lpl.loop_point(i).selected()) {
      if (!sel.size())
        sel.begin_ = i;
      sel.end_ = i + 1;
    }
  }
  return sel;
}

template <typename Op>
void selOne(Op op, LoopPointList* lpl, bool sel, bool unselOthers = false) {
  int index = mod((*op)(getSelection(*lpl)), lpl->loop_point_size());
  if (unselOthers) {
    for (int i = 0; i < lpl->loop_point_size(); ++i)
      lpl->mutable_loop_point(i)->set_selected(false);
  }
  lpl->mutable_loop_point(index)->set_selected(sel);
}

int getEnd(const Range<int>& sel) { return sel.end_; }
int preEnd(const Range<int>& sel) { return sel.end_ - 1; }
int getBegin(const Range<int>& sel) { return sel.begin_; }
int preBegin(const Range<int>& sel) { return sel.begin_ - 1; }

void extendEndL(LoopPointList* p) { selOne(&getEnd, p, true); }
void retractEndL(LoopPointList* p) { selOne(&preEnd, p, false); }
void extendBeginL(LoopPointList* p) { selOne(&preBegin, p, true); }
void retractBeginL(LoopPointList* p) { selOne(&getBegin, p, false); }
void selectNextOnlyL(LoopPointList* p) { selOne(&getEnd, p, true, true); }
void selectPreviousOnlyL(LoopPointList* p) { selOne(&preBegin, p, true, true); }

}  // namespace

void addLoopPoint(Instance* i) {
  i->components_->loops_.addLoopPoint(i->player_->getTime());
}

void selectAll(Instance* i) { apply(&selectAll2, i); }
void selectNone(Instance* i) { apply(&selectNone2, i); }
void selectInvert(Instance* i) { apply(&selectInvert2, i); }

void extendEnd(Instance* i) { apply(&extendEndL, i); }
void retractEnd(Instance* i) { apply(&retractEndL, i); }
void extendBegin(Instance* i) { apply(&extendBeginL, i); }
void retractBegin(Instance* i) { apply(&retractBeginL, i); }
void selectNextOnly(Instance* i) { apply(&selectNextOnlyL, i); }
void selectPreviousOnly(Instance* i) { apply(&selectPreviousOnlyL, i); }

void selectItem(Instance* i, int index) { Selecter(index, SET).set(i); }
void selectItemOnly(Instance* i, int index) { Selecter(index, ONLY).set(i); }
void unselectItem(Instance* i, int index) { Selecter(index, RESET).set(i); }
void toggleItem(Instance* i, int index) { Selecter(index, TOGGLE).set(i); }

}  // namespace slow
}  // namespace rec
