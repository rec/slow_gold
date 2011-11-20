#include <algorithm>

#include "rec/base/RealTime.h"
#include "rec/data/yaml/Yaml.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/audio/Loops.h"
#include "rec/util/Defaulter.h"
#include "rec/util/FormatTime.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/Math.h"
#include "rec/util/Range.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {
namespace audio {

using data::Address;
using data::Value;
using gui::TableColumn;
using rec::audio::getSelected;

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
      DataListener<LoopPointList>(a),
      length_(0.0) {
  initialize(dflt.get(desc), a, "Loops");
  fillHeader(&getHeader());
  setMultipleSelectionEnabled(true);
}

Loops::~Loops() {}

void Loops::onDataChange(const LoopPointList& loops) {
  length_ = loops.length();
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
  LoopPointList loops = data()->get();
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
    data()->setValue(loops);
}

void Loops::update() {
  bool changed;
  LoopPointList loops = data()->get();

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

string Loops::copy() const {
  return yaml::write(getSelected(data()->get(), true));
}

bool Loops::canCopy() const {
  return getSelected(data()->get(), true).loop_point_size();
}

bool Loops::canCut() const {
  LoopPointList lpl = getSelected(data()->get(), true);
  int size = lpl.loop_point_size();
  return (size > 1) || (size == 1 && !lpl.loop_point(0).selected());
}

void Loops::cut() {
  LoopPointList lpl = data()->get();
  if (lpl.loop_point_size())
    lpl.mutable_loop_point(0)->set_selected(false);
  data()->setValue(getSelected(lpl, false));
}

bool Loops::paste(const string& s) {
  LoopPointList loops;
  if (yaml::read(s, &loops)) {
    data()->setValue(rec::audio::addLoopPoints(data()->get(), loops));
    return true;
  }
  return false;
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
