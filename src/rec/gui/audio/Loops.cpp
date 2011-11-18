#include <algorithm>

#include "rec/base/RealTime.h"
#include "rec/data/yaml/Yaml.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/audio/Loops.h"
#include "rec/util/Defaulter.h"
#include "rec/util/FormatTime.h"
#include "rec/util/Math.h"
#include "rec/util/Range.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {
namespace audio {

using data::Address;
using data::Value;
using gui::TableColumn;

static Def<TableColumnList> dflt(
"column { type: TIME name: \"Time\" address { part { name: \"time\" } } } "
"column { "
"type: STRING "
"name: \"Name\" "
"address { part { name: \"name\" } } "
"width: 170 "
"maximum_width: 300 "
"} "
#if 0
"column { type: STRING name: \"Notes\" address { part { name: \"notes\" } } } "
#endif
);

const RealTime Loops::CLOSE = 0.5;

Loops::Loops(MenuBarModel* menus, const TableColumnList* desc, const Address& a)
    : component::Focusable<TableController>(menus),
      DataListener<LoopPointList>(a) {
  initialize(dflt.get(desc), a, "Loops");
  fillHeader(&getHeader());
  setMultipleSelectionEnabled(true);
}

Loops::~Loops() {}

void Loops::onDataChange(const LoopPointList&) {
  MessageManagerLock l;
  update();
}

static String getDisplayText(const Value& v, const TableColumn& col, RealTime length) {
  switch (col.type()) {
   case TableColumn::STRING: return str(v.string_f());
   case TableColumn::UINT32: return String(v.uint32_f());
   case TableColumn::TIME: return formatTime(RealTime(v.double_f()), length);
   case TableColumn::DOUBLE: return String(v.double_f());

   default: return "<unknown>";
  }
}

String Loops::displayText(const TableColumn& col, int rowIndex) {
  String t = "-";
  if (data()) {
    Address row = (address() + rowIndex) + col.address();
    t = getDisplayText(data()->getValue(row), col, length_);
  }
  return t;
}

void Loops::selectedRowsChanged(int lastRowSelected) {
  bool changed = false;
  LoopPointList loops = get();
  juce::SparseSet<int> selected(getSelectedRows());

  for (int i = 0; i < loops.loop_point_size(); ++i) {
    LoopPoint* lp = loops.mutable_loop_point(i);
    bool contains = selected.contains(i);
    if (lp->selected() != contains) {
      lp->set_selected(contains);
      changed = true;
    }
  }
  if (changed)
    set(loops);
}

void Loops::update() {
  bool changed;
  LoopPointList loops = get();

  juce::SparseSet<int> sel;
  for (int i = 0; i < loops.loop_point_size(); ++i) {
    if (loops.loop_point(i).selected())
      sel.addRange(juce::Range<int>(i, i + 1));

    changed = (sel != getSelectedRows());
  }
  if (changed)
    setSelectedRows(sel, false);

  TableController::update();
}

bool Loops::isNewLoopPoint(RealTime t) const {
  if (!data())
    return false;

  const LoopPointList loops = get();
  for (int i = 0; i < loops.loop_point_size(); ++i) {
    RealTime t2 = loops.loop_point(i).time();
    RealTime x = t;
    RealTime y = t2;
    RealTime z = Loops::CLOSE;
    //if (util::near<RealTime>(t, t2, Loops::CLOSE))
    if (Math<RealTime>::near(x, y, z))
      return false;
  }
  return true;
}

void Loops::setLoopPoints(const LoopPointList& loops) {
  set(loops);
  updateAndRepaint();  // TODO: is this needed?
}

namespace {

struct CompareLoopPoints {
  bool operator()(const LoopPoint& x, const LoopPoint& y) const {
    return x.time() < y.time();
  }
};

}  // namespace

LoopPointList Loops::getSelected(bool selected) const {
  LoopPointList loops = get();
  LoopPointList result;

  for (int i = 0, size = loops.loop_point_size(); i < size; ++i) {
    if (loops.loop_point(i).selected() == selected || i == size - 1)
      result.add_loop_point()->CopyFrom(loops.loop_point(i));
  }
  return result;
}

string Loops::copy() const {
  return yaml::write(getSelected(true));
}

bool Loops::canCopy() const {
  return getSelected(true).loop_point_size();
}

void Loops::cut() {
  set(getSelected(false));
}

void Loops::addLoopPoints(const LoopPointList& lpl) {
  if (!data())
    return;

  LoopPointList loops = get();
  for (int i = 0, j = 0; i < lpl.loop_point_size(); ++i) {
    double t = lpl.loop_point(i).time();
    if (isNewLoopPoint(t)) {
      LoopPoint* lp = loops.add_loop_point();
      lp->CopyFrom(lpl.loop_point(i));
      for (; j < loops.loop_point_size() && loops.loop_point(j).time() <= t; ++j);
    }
  }

  std::sort(loops.mutable_loop_point()->begin(),
            loops.mutable_loop_point()->end(),
            CompareLoopPoints());

  set(loops);
  updateAndRepaint();  // TODO
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



