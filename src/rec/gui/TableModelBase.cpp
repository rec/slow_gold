#include "rec/gui/TableModelBase.h"
#include "rec/widget/status/Time.h"
#include "rec/data/proto/Proto.h"

using namespace juce;

namespace rec {
namespace gui {

TableModelBase::TableModelBase(const TableColumnList& c)
    : TableListBox("TableModelBase", this), columns_(c) {
}

void TableModelBase::fillHeaders(TableHeaderComponent* headers) {
  ScopedLock l(lock_);
  for (int i = 0; i < columns_.column_size(); ++i)  {
    const TableColumn& col = columns_.column(i);
    headers->addColumn(col.name().c_str(), i, col.width(), col.minimum_width(),
                       col.maximum_width(), col.property_flags());
  }
}

int TableModelBase::getNumRows() {
  ScopedLock l(lock_);
  return proto::getSize(address(), message());
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

  const TableColumn& column = columns_.column(columnId);
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

}  // namespace gui
}  // namespace rec
