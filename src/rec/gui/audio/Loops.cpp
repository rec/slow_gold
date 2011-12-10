#include <algorithm>

#include "rec/base/Samples.h"
#include "rec/data/yaml/Yaml.h"
#include "rec/data/proto/Equals.h"
#include "rec/gui/SetterText.h"
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

// TODO: i18n

static const juce::Colour UNSELECTED_COLOR = juce::Colours::white;
static const juce::Colour SELECTED_COLOR(0xffefef80);

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
"} "
);

Loops::Loops(MenuBarModel* menus, const TableColumnList* desc, const Address& a)
    : component::Focusable<TableController>(menus),
      DataListener<LoopPointList>(a) {
  initialize(dflt.get(desc), a, "Loops");
  fillHeader(&getHeader());
  setMultipleSelectionEnabled(true);
}

Loops::~Loops() {}

void Loops::onDataChange(const LoopPointList& loops) {
  {
    Lock l(TableController::lock_);
    loops_ = loops;
  }

  thread::callAsync(this, &Loops::updateAndRepaint);
}

static String getDisplayText(const Value& v, const TableColumn& col, Samples<44100> length) {
  switch (col.type()) {
   case TableColumn::STRING:  return str(v.string_f());
   case TableColumn::UINT32:  return String(v.uint32_f());
   case TableColumn::TIME:    return formatTime(Samples<44100>(v.int64_f()), length);
   case TableColumn::DOUBLE:  return String(v.double_f());
   default:                   return "<unknown>";
  }
}

String Loops::displayText(const TableColumn& col, int rowIndex) {
  Address row = Address(rowIndex) + col.address();
  return getDisplayText(getValue(row), col, Samples<44100>(loops_.length()));
}

void Loops::selectedRowsChanged(int lastRowSelected) {
  Lock l(TableController::lock_);
  bool changed = false;

  juce::SparseSet<int> selected(getSelectedRows());

  for (int i = 0; i < loops_.loop_point_size(); ++i) {
    LoopPoint* lp = loops_.mutable_loop_point(i);
    bool contains = selected.contains(i);
    if (lp->selected() != contains) {
      lp->set_selected(contains);
      changed = true;
    }
  }
  if (changed)
    setValue(loops_);
}

void Loops::update() {
  TableController::update();

  Lock l(TableController::lock_);

  juce::SparseSet<int> sel;
  for (int i = 0; i < loops_.loop_point_size(); ++i) {
    if (loops_.loop_point(i).selected())
      sel.addRange(juce::Range<int>(i, i + 1));
  }

  if (sel != getSelectedRows())
    setSelectedRows(sel, false);
}

string Loops::copy() const {
  Lock l(TableController::lock_);
  return yaml::write(getSelected(loops_, true));
}

bool Loops::canCopy() const {
  Lock l(TableController::lock_);
  return getSelected(loops_, true).loop_point_size();
}

bool Loops::canCut() const {
  Lock l(TableController::lock_);
  LoopPointList lpl = getSelected(loops_, true);
  int size = lpl.loop_point_size();
  return (size > 1) || (size == 1 && lpl.loop_point(0).has_time());
}

void Loops::cut() {
  bool firstWasSelected = loops_.loop_point(0).selected();
  if (loops_.loop_point_size())
    loops_.mutable_loop_point(0)->set_selected(false);
  LoopPointList loops = getSelected(loops_, false);
  if (loops.loop_point_size())
    loops.mutable_loop_point(0)->set_selected(firstWasSelected);

  loops_ = loops;
  setValue(loops_);
}

bool Loops::paste(const string& s) {
  LoopPointList loops;
  if (yaml::read(s, &loops)) {
    loops_ = rec::audio::addLoopPoints(loops_, loops);
    setValue(loops_);
    return true;
  }
  return false;
}

using data::Address;

class LoopsSetterText : public SetterText<LoopPointList> {
 public:
  explicit LoopsSetterText(int row, const TableColumn& col)
      : SetterText<LoopPointList>("",
                                  "loop_point" + Address(row) + col.address(),
                                  "", "", false) {

  }

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(LoopsSetterText);
};

Component* Loops::refreshComponentForCell(int row, int column,
                                          bool isRowSelected,
                                          Component* existing) {
  if (!existing) {
    if (column > columns().column_size()) {
      LOG(DFATAL) << "Unexpected column: " << column
                 << ", " << columns().column_size();
    } else {
      const TableColumn& col = columns().column(column - 1);
      if (col.type() == TableColumn::STRING) {
        ptr<LoopsSetterText> lst(new LoopsSetterText(row, col));
        lst->setTooltip("This is the name of the loop, and you can edit "
                             "it by clicking here.");
        existing = lst.transfer();
        UpdateRequester::requestAllUpdates();
      }
    }
  }
  if (existing) {
    LoopsSetterText* text = dynamic_cast<LoopsSetterText*>(existing);
    if (text)
      text->setEditorBackground(isRowSelected ? SELECTED_COLOR : UNSELECTED_COLOR);
    else
      LOG(DFATAL) << "Wrong component type!";
  }
  return existing;
}


}  // namespace audio
}  // namespace gui
}  // namespace rec
