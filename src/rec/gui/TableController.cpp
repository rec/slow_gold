#include "rec/gui/TableController.h"
#include "rec/widget/status/Time.h"
#include "rec/data/proto/Proto.h"
#include "rec/data/proto/Setter.h"
#include "rec/util/thread/CallAsync.h"

namespace rec {
namespace gui {

TableController::TableController(const TableColumnList& c, const Address& address)
    : TableListBox("TableController", this),
      columns_(c),
      setter_(NULL),
      address_(address),
      numRows_(0) {
}

void TableController::fillHeader(TableHeaderComponent* headers) {
  ScopedLock l(lock_);
  for (int i = 0; i < columns_.column_size(); ++i)  {
    const TableColumn& col = columns_.column(i);
    headers->addColumn(col.name().c_str(), i + 1, col.width(), col.minimum_width(),
                       col.maximum_width(), col.property_flags());
  }
}

int TableController::getNumRows() {
  ScopedLock l(lock_);
  return numRows_;
}

void TableController::paintRowBackground(Graphics& g,
                                        int rowNumber,
                                        int width, int height,
                                        bool rowIsSelected) {
  ScopedLock l(lock_);
  g.setColour(rowIsSelected ? juce::Colour(0xffefef80) : juce::Colours::white);
  g.fillRect(0, 0, width, height);
}

void TableController::paintCell(Graphics& g,
                               int rowNumber,
                               int columnId,
                               int width, int height,
                               bool rowIsSelected) {
  ScopedLock l(lock_);
  g.setColour(juce::Colours::black);
  if (columnId > columns_.column_size() || columnId <= 0) {
    LOG(ERROR) << "columnId " << columnId << " size " << columns_.column_size();
    return;
  }
  const TableColumn& column = columns_.column(columnId - 1);
  Address row = (address_ + rowNumber) + column.address();
  String t = displayText(column, proto::getValue(row, message()));
  g.drawText(t, 2, 2, width - 4, height - 4, Justification::centred, true);
}

String TableController::displayText(const TableColumn& col, const Value& value) {
  switch (col.type()) {
   case TableColumn::STRING: return toString(value);
   case TableColumn::UINT32: return String(static_cast<uint32>(value));
   case TableColumn::TIME: return widget::status::time::formatTime(value, false, false);
   case TableColumn::DOUBLE: return String(static_cast<double>(value));

   default: return "<unknown>";
  }
}

const Value TableController::get() const {
  ScopedLock l(lock_);
  Value value;
  message().SerializeToString(value.mutable_message_f());
  return value;
}

void TableController::onDataChange() {
  {
    ScopedLock l(lock_);
    numRows_ = proto::getSize(address_, message());
  }
  thread::callAsync(this, &TableListBox::updateContent);
}

void TableController::set(const Value& v) {
  ScopedLock l(lock_);
  if (!mutable_message()->ParseFromString(v.message_f()))
    LOG(ERROR) << "Couldn't parse value: " << message().DebugString();
}

void TableController::setSetter(Setter* setter) {
  {
    ScopedLock l(lock_);
    setter_ = setter;
    numRows_ = 0;
  }
  if (Message* msg = mutable_message()) {
    if (setter)
      setter->copyTo(msg);
    else
      msg->Clear();
  }
  onDataChange();
}

void TableController::selectedRowsChanged(int lastRowSelected) {
  juce::SparseSet<int> s;
  {
    ScopedLock l(lock_);
    s = getSelectedRows();
  }
  broadcast(s);
}

}  // namespace gui
}  // namespace rec
