#include <algorithm>

#include "rec/gui/audio/Loops.h"

#include "rec/base/Samples.h"
#include "rec/data/DataOps.h"
#include "rec/data/proto/Equals.h"
#include "rec/data/proto/FieldOps.h"
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
using namespace rec::widget::waveform;

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
  tcl.mutable_column(0)->set_name(str(Trans("Time")));
  tcl.mutable_column(1)->set_name(str(Trans("Name")));
  initialize(tcl, "Loops");
  fillHeader(&getHeader());
  setMultipleSelectionEnabled(true);
  setTooltip(Trans("Loop Point List: You can select and edit loop points here."));
}

Loops::~Loops() {}

int Loops::getNumRows() {
  Lock l(TableController::lock_);
  return viewport_.loop_points().loop_point_size();
}

void Loops::operator()(const Viewport& vp) {
  setViewport(vp);
}


void Loops::setViewport(const Viewport& viewport) {
  {
    Lock l(TableController::lock_);
    viewport_ = viewport;
  }

  thread::callAsync(this, &Loops::updateAndRepaint);
}

static String getDisplayText(const Value& v, const TableColumn& col,
                             Samples<44100> length, int sampleRate) {
  switch (col.type()) {
   case TableColumn::STRING:  return str(v.string_f());
   case TableColumn::UINT32:  return String(v.uint32_f());
   case TableColumn::TIME:    return formatTime(Samples<44100>(v.int64_f()), length,
                                                sampleRate, false, true, 0);
   case TableColumn::DOUBLE:  return String(v.double_f());
   default:                   return "<unknown>";
  }
}

String Loops::displayText(int colIndex, int rowIndex) const {
  const TableColumn& col = columns_.column(colIndex);
  Address row = partAddress_ + Address(rowIndex) + col.address();
  data::Value value;
  string error = getMessageField(row, getProto(), &value);
  if (!error.empty()) {
    LOG(ERROR) << error << ",\n" << row.DebugString();
    return Trans("(error)"); // TODO
  }

  Samples<44100> length = Samples<44100>(viewport_.loop_points().length());
  return getDisplayText(value, col, length, 44100);
}

void Loops::selectedRowsChanged(int /*lastRowSelected*/) {
  Viewport viewport;
  bool changed = false;
  {
    Lock l(TableController::lock_);

    juce::SparseSet<int> selected(getSelectedRows());

    for (int i = 0; i < getNumRows(); ++i) {
      LoopPoint* lp = viewport_.mutable_loop_points()->mutable_loop_point(i);
      bool contains = selected.contains(i);
      if (lp->selected() != contains) {
        lp->set_selected(contains);
        changed = true;
      }
    }
    viewport = viewport_;
  }
  if (changed)
    setProto(viewport);
}

void Loops::update() {
  TableController::update();

  juce::SparseSet<int> sel;
  {
    Lock l(TableController::lock_);
    for (int i = 0; i < getNumRows(); ++i) {
      if (viewport_.loop_points().loop_point(i).selected())
        sel.addRange(juce::Range<int>(i, i + 1));
    }
  }

  if (sel != getSelectedRows())
    setSelectedRows(sel, false);
}

class LoopsSetterLabel : public SimpleLabel {
 public:
  explicit LoopsSetterLabel(Loops* loops, int col, int row)
      : SimpleLabel(""), loops_(loops), col_(col), row_(row) {
    setEditable(true, false, false);
    setJustificationType(Justification::centredLeft);
  }

  void setEditorBackground(const juce::Colour& c) {
    setColour(juce::Label::backgroundColourId, c);
  }

  virtual void textEditorTextChanged(TextEditor&) {
    loops_->setFieldValue(col_, row_, getText(true));
  }

 private:
  Loops* const loops_;
  const int col_;
  const int row_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(LoopsSetterLabel);
};

void Loops::setFieldValue(int row, int column, const String& text) {
  DCHECK(false);
}

Component* Loops::refreshComponentForCell(int row, int column,
                                          bool isRowSelected,
                                          Component* existing) {
  if (!existing) {
    if (column > columns().column_size()) {
      LOG(DFATAL) << "Unexpected column: " << column
                 << ", " << columns().column_size();
    } else {
      if (columns().column(column - 1).type() == TableColumn::STRING) {
        ptr<LoopsSetterLabel> lst(new LoopsSetterLabel(this, row, column - 1));
        lst->setText(displayText(row, column), false);
        lst->setTooltip(Trans("Loop Point Name: Edit the Loop Point's name "
                                  "by clicking here."));
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

void Loops::editViewport(const widget::waveform::Viewport& viewport) {
  setViewport(viewport);
  updateContent();
  setProto(viewport);
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
