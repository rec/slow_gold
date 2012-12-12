#include <algorithm>

#include "rec/gui/audio/Loops.h"

#include "rec/audio/source/Player.h"
#include "rec/base/SampleTime.h"
#include "rec/data/DataCenter.h"
#include "rec/data/DataOps.h"
#include "rec/data/UndoStack.h"
#include "rec/data/proto/Equals.h"
#include "rec/data/proto/FieldOps.h"
#include "rec/gui/SetterText.h"
#include "rec/gui/audio/LoopsCuttable.h"
#include "rec/slow/Instance.h"
#include "rec/util/FormatTime.h"
#include "rec/util/LoopPoint.h"
#include "rec/util/Math.h"
#include "rec/util/proto/Defaulter.h"
#include "rec/util/range/Range.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/widget/waveform/Cursor.h"

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
"  width: 60 "
"  property_flags: DEFAULT_NOT_EDITABLE"
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
  setMultipleSelectionEnabled(true);

  TableColumnList tcl = dflt.get(NULL);
  tcl.mutable_column(0)->set_name(str(Trans("Time")));
  tcl.mutable_column(1)->set_name(str(Trans("Name")));
  initialize(tcl, "Loops");
  fillHeader(&getHeader());
}

Loops::~Loops() {}

int Loops::getNumRows() {
  Lock l(TableController::lock_);
  return viewport_.loop_points().loop_point_size();
}

void Loops::operator()(const Viewport& vp) {
  setViewport(vp);
}

void Loops::languageChanged() {
  setTooltip(Trans("Loop Point List: You can select and edit loop points here."));
  TableHeaderComponent& header = getHeader();
  header.setColumnName(1, Trans("Time"));
  header.setColumnName(2, Trans("Name"));
}

void Loops::setViewport(const Viewport& viewport) {
  {
    Lock l(TableController::lock_);
    viewport_ = viewport;
  }

  update();
  repaint();
}

String Loops::displayText(int column, int row) const {
  Address rowAddress = getAddress(column, row);
  data::Value v;
  string error = getMessageField(rowAddress, getDataValue(), &v);
  if (!error.empty()) {
    LOG(ERROR) << row << "," << column << ": " << error;
    return Trans("(error)");
  }

  SampleTime len = SampleTime(viewport_.loop_points().length());
  switch (columns_.column(column).type()) {
   case TableColumn::STRING:  return str(v.string_f());
   case TableColumn::UINT32:  return String(v.uint32_f());
   case TableColumn::DOUBLE:  return String(v.double_f());
   case TableColumn::TIME:
    return TimeFormat(TimeFormat::NO_FLASH, TimeFormat::LEADING_ZEROS, 0).
      format(v.int64_f(), len, viewport_.loop_points().sample_rate());
   default:                   return "<unknown>";
  }
}

void Loops::setFieldValue(int column, int row, const String& text) {
  Lock l(TableController::lock_);
  Address rowAddress = getAddress(column, row);
  data::Value value(str(text));
  string error = setMessageField(rowAddress, &viewport_, value);
  if (error.empty())
    setProto(viewport_);
  else
    LOG(ERROR) << error << ",\n" << rowAddress.DebugString();
}

void Loops::selectedRowsChanged(int) {
  Lock l(TableController::lock_);

  bool changed = false;
  juce::SparseSet<int> selected(getSelectedRows());
  for (int i = 0; i < getNumRows(); ++i) {
    LoopPoint* lp = viewport_.mutable_loop_points()->mutable_loop_point(i);
    bool contains = selected.contains(i);
    if (lp->selected() != contains) {
      lp->set_selected(contains);
      changed = true;
    }
  }
  if (changed)
    setProto(viewport_);
}

void Loops::cellDoubleClicked(int rowNumber, int, const MouseEvent&) {
  LoopPointList* lpl = viewport_.mutable_loop_points();
  for (int i = 0; i < lpl->loop_point_size(); ++i)
    lpl->mutable_loop_point(i)->set_selected(i == rowNumber);
  setProto(viewport_);
  slow::Instance::getInstance()->player_->start();
}

bool Loops::selected(int r) const {
  Lock l(TableController::lock_);
  const LoopPointList& lpl = viewport_.loop_points();
  return r >= 0 && r < lpl.loop_point_size() && lpl.loop_point(r).selected();
}

void Loops::update() {
  int rows;
  int columns;
  juce::SparseSet<int> sel;
  {
    Lock l(TableController::lock_);  // Perhaps simplify locking here?
    rows = getNumRows();
    columns = columns_.column_size();
    for (int r = 0; r < rows; ++r) {
      bool selected = viewport_.loop_points().loop_point(r).selected();
      if (selected)
        sel.addRange(juce::Range<int>(r, r + 1));
    }
  }

  if (sel != getSelectedRows())
    setSelectedRows(sel, juce::dontSendNotification);
  updateContent();
  TableController::update();
  repaint();
}

String Loops::getCellTooltip(int, int) const {
  return t_LOOP_POINT_CAPTION;
}

void Loops::editViewport(const widget::waveform::Viewport& viewport) {
  setViewport(viewport);
  updateContent();
  setProto(viewport);
}

void Loops::setEditing(bool editing) {
  data::UndoStack* stack = data::getDataCenter().undoStack();
  if (editing)
    stack->startGroup();
  else
    stack->stopGroup();
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
