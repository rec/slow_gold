#include "rec/gui/TableController.h"
#include "rec/data/proto/Proto.h"
#include "rec/data/Data.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/FormatTime.h"

namespace rec {
namespace gui {

TableController::TableController() : TableListBox("", this),
                                     ProtoListener(Address()) {
}

void TableController::initialize(const TableColumnList& c, const Address& address,
                                 const char* name) {
  columns_ = c;
  address_ = address;
  setName(name);
}

void TableController::fillHeader(TableHeaderComponent* headers) {
  ScopedLock l(lock_);
  for (int i = 0; i < columns_.column_size(); ++i)  {
    const TableColumn& col = columns_.column(i);
    headers->addColumn(col.name().c_str(), i + 1, col.width(), col.minimum_width(),
                       col.maximum_width(), col.property_flags());
  }
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
  String t = displayText(column, data::getValue(row, *message_));
  g.drawText(t, 2, 2, width - 4, height - 4, Justification::centred, true);
}

String TableController::displayText(const TableColumn& col, const Value& value) {
  switch (col.type()) {
   case TableColumn::STRING: return toString(value);
   case TableColumn::UINT32: return String(static_cast<uint32>(value));
   case TableColumn::TIME: return formatTime(value, false, true, false, 0);
   case TableColumn::DOUBLE: return String(static_cast<double>(value));

   default: return "<unknown>";
  }
}

const Value TableController::getDisplayValue() const {
  ScopedLock l(lock_);
  Value value;
  message_->SerializeToString(value.mutable_message_f());
  return value;
}

void TableController::setDisplayValue(const Value& v) {
  ScopedLock l(lock_);
  if (message_.get()->ParseFromString(v.message_f())) {
    thread::callAsync(this, &TableController::updateAndRepaint);
  } else {
    LOG(ERROR) << "Couldn't parse value: " << message_->DebugString();
  }
}

void TableController::setData(data::UntypedData* data) {
  {
    ScopedLock l(lock_);
    ProtoListener::setData(data);
  }

  if (Message* msg = message_.get()) {
    if (data)
      data->copyTo(msg);
    else
      msg->Clear();
  }
}

}  // namespace gui
}  // namespace rec
