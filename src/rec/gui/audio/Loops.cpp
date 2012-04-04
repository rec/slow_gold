#include <algorithm>

#include "rec/gui/audio/Loops.h"

#include "rec/base/Samples.h"
#include "rec/data/DataOps.h"
#include "rec/data/proto/Equals.h"
#include "rec/data/proto/FieldOps.h"
#include "rec/gui/SetterLabel.h"
#include "rec/gui/SetterText.h"
#include "rec/gui/audio/LoopsCuttable.h"
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

// Skin

namespace {

const juce::Colour UNSELECTED_COLOR = juce::Colours::white;
const juce::Colour SELECTED_COLOR(0xffefef80);

Def<TableColumnList> dflt(
"column { "
"  type: TIME "
"  name: \"Time\" "
"  address { part { name: \"time\" } } "
"  width: 50 "
"} "
"column { "
"  type: STRING "
"  name: \"Name\" "
"  address { part { name: \"name\" } } "
"  width: 170 "
"} "
);

}  // namespace

Loops::Loops(const TableColumnList* desc,
             const Address& partAddress)
    : partAddress_(partAddress) {
  cuttable_.reset(new LoopsCuttable(this));
  TableColumnList tcl = dflt.get(desc);
  tcl.mutable_column(0)->set_name(str(trans("Time")));
  tcl.mutable_column(1)->set_name(str(trans("Name")));
  initialize(tcl, "Loops");
  fillHeader(&getHeader());
  setMultipleSelectionEnabled(true);
  setTooltip(trans("Loop Point List: You can select and edit loop points here."));
}

Loops::~Loops() {}

int Loops::getNumRows() {
  Lock l(TableController::lock_);
  return loops_.loop_point_size();
}

void Loops::operator()(const LoopPointList& loops) {
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
   case TableColumn::TIME:    return formatTime(Samples<44100>(v.int64_f()),
                                                length, false, true, 0);
   case TableColumn::DOUBLE:  return String(v.double_f());
   default:                   return "<unknown>";
  }
}

String Loops::displayText(const TableColumn& col, int rowIndex) {
  Address row = partAddress_ + Address(rowIndex) + col.address();
  data::Value value;
  string error = getMessageField(row, getProto(), &value);
  return error.empty() ?
    getDisplayText(value, col, Samples<44100>(loops_.length())) : trans("(error)");
}

void Loops::selectedRowsChanged(int /*lastRowSelected*/) {
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
    setProto(loops_);
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

using data::Address;

class LoopsSetterLabel : public SetterLabel {
 public:
  explicit LoopsSetterLabel(int row, const TableColumn& col)
      : SetterLabel("",
                    getTypeName<LoopPointList>(),
                    "loop_point" + Address(row) + col.address()),
        row_(row) {
    setEditable(true, false, false);
    setFailOnError(false);
    setJustificationType(Justification::centredLeft);
  }

 protected:
  virtual void operator()(const Message& m) {
    // Juce takes some time to delete this item, and it might get an update
    // at a point when it no longer points to a valid item in the LoopPointList.
    if (const LoopPointList* lpl = dynamic_cast<const LoopPointList*>(&m)) {
      if (row_ < lpl->loop_point_size())
        SetterLabel::operator()(m);
    }
  }

 private:
  CriticalSection lock_;
  int row_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(LoopsSetterLabel);
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
        ptr<LoopsSetterLabel> lst(new LoopsSetterLabel(row, col));
        lst->setTooltip(trans("Loop Point Name: Edit the Loop Point's name "
                                  "by clicking here."));
        lst->startListening();
        existing = lst.transfer();
      }
    }
  }
  if (existing) {
    LoopsSetterLabel* text = dynamic_cast<LoopsSetterLabel*>(existing);
    if (text)
      text->setEditorBackground(isRowSelected ? SELECTED_COLOR : UNSELECTED_COLOR);
    else
      LOG(DFATAL) << "Wrong component type!";
  }
  return existing;
}

void Loops::editLoopPoints(const LoopPointList& lpl) {
  operator()(lpl);
  updateContent();
  setProto(lpl);
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
