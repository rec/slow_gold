#include "rec/gui/TableModelBase.h"
#include "rec/widget/status/Time.h"
#include "rec/data/proto/Proto.h"
#include "rec/util/thread/CallAsync.h"

using namespace juce;

namespace rec {
namespace gui {

TableModelBase::TableModelBase(const TableColumnList& c)
    : TableListBox("TableModelBase", this), columns_(c), setter_(NULL) {
}

void TableModelBase::fillHeader(TableHeaderComponent* headers) {
  ScopedLock l(lock_);
  for (int i = 0; i < columns_.column_size(); ++i)  {
    const TableColumn& col = columns_.column(i);
    headers->addColumn(col.name().c_str(), i + 1, col.width(), col.minimum_width(),
                       col.maximum_width(), col.property_flags());
  }
}

int TableModelBase::getNumRows() {
  ScopedLock l(lock_);
  int size = proto::getSize(address(), message());
  return size;
}

void TableModelBase::paintRowBackground(Graphics& g,
                                        int rowNumber,
                                        int width, int height,
                                        bool rowIsSelected) {
  ScopedLock l(lock_);
  g.setColour(rowIsSelected ? juce::Colours::yellow : juce::Colours::white);
  g.fillRect(0, 0, width, height);
}

void TableModelBase::paintCell(Graphics& g,
 int rowNumber,
                               int columnId,
                               int width, int height,
                               bool rowIsSelected) {
  ScopedLock l(lock_);

  const TableColumn& column = columns_.column(columnId - 1);
  Address addr = address();
  addr.add_field()->set_index(rowNumber);
  addr.MergeFrom(column.address());
  String t = displayText(column, proto::getValue(addr, message()));
  g.drawText(t, 2, 2, width - 4, height - 4, Justification::centred, true);
}

String TableModelBase::displayText(const TableColumn& col, const Value& value) {
  switch (col.type()) {
   case TableColumn::STRING: return toString(value);
   case TableColumn::UINT32: return String(static_cast<uint32>(value));
   case TableColumn::TIME: return widget::status::time::formatTime(value, false, false);
   case TableColumn::DOUBLE: return String(static_cast<double>(value));

   default: return "<unknown>";
  }
}

const Value TableModelBase::get() const {
  ScopedLock l(lock_);
  Value value;
  message().SerializeToString(value.mutable_message_f());
  return value;
}

void TableModelBase::set(const Value& v) {
  ScopedLock l(lock_);

  if (!mutable_message()->ParseFromString(v.message_f()))
    LOG(ERROR) << "Couldn't parse value: " << message().DebugString();

  thread::callAsync(this, &TableListBox::updateContent);
}

void TableModelBase::selectedRowsChanged(const juce::SparseSet<int>& selected) {
  for (int i = 0, done = 0; i < selected.getNumRanges(); ++i) {
    juce::Range<int> range = selected.getRange(i);
    for (; done < range.getStart(); ++done)
      setSelected(done, false);

    for (; done != range.getEnd(); ++done)
      setSelected(done, true);
  }
}

}  // namespace gui
}  // namespace rec
