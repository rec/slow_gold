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

String Loops::displayText(int column, int row) const {
  Address rowAddress = getAddress(column, row);
  data::Value v;
  string error = getMessageField(rowAddress, getProto(), &v);
  if (!error.empty()) {
    LOG(ERROR) << error << ",\n" << rowAddress.DebugString();
    return Trans("(error)"); // TODO
  }

  Samples<44100> length = Samples<44100>(viewport_.loop_points().length());
  switch (columns_.column(column).type()) {
   case TableColumn::STRING:  return str(v.string_f());
   case TableColumn::UINT32:  return String(v.uint32_f());
   case TableColumn::TIME:    return formatTime(Samples<44100>(v.int64_f()), length,
                                                44100, false, true, 0);
   case TableColumn::DOUBLE:  return String(v.double_f());
   default:                   return "<unknown>";
  }
}

void Loops::setFieldValue(int column, int row, const String& text) {
  Lock l(TableController::lock_);
  Address rowAddress = getAddress(column, row);
  data::Value value;
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

void Loops::update() {
  TableController::update();

  juce::SparseSet<int> sel;
  {
    Lock l(TableController::lock_);  // TODO: simplify locking here?
    for (int i = 0; i < getNumRows(); ++i) {
      if (viewport_.loop_points().loop_point(i).selected())
        sel.addRange(juce::Range<int>(i, i + 1));
    }
  }

  if (sel != getSelectedRows())
    setSelectedRows(sel, false);
}

String Loops::getCellTooltip(int, int) const {
  return Trans("Loop Point Name: Edit the Loop Point's name "
               "by clicking here.");
}

void Loops::editViewport(const widget::waveform::Viewport& viewport) {
  setViewport(viewport);
  updateContent();
  setProto(viewport);
}

}  // namespace audio
}  // namespace gui
}  // namespace rec
