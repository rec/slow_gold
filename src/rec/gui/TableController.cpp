#include "rec/gui/TableController.h"
#include "rec/data/Editable.h"
#include "rec/data/Value.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/Copy.h"

namespace rec {
namespace gui {

using data::Address;
using data::Value;

TableController::TableController() : TableListBox("", this) {}

void TableController::initialize(const TableColumnList& c, const Address& address, const char* name) {
  columns_ = c;
  setName(name);
}

void TableController::fillHeader(TableHeaderComponent* headers) {
  ScopedLock l(lock_);
  for (int i = 0; i < columns_.column_size(); ++i)  {
    const TableColumn& col = columns_.column(i);
    headers->addColumn(str(col.name()), i + 1, col.width(), col.minimum_width(),
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
  String t = displayText(column, rowNumber);
  g.drawText(t, 2, 2, width - 4, height - 4, Justification::centred, true);
}

}  // namespace gui
}  // namespace rec
