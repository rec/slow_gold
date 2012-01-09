#include "rec/gui/TableController.h"
#include "rec/data/Value.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/Copy.h"

namespace rec {
namespace gui {

static const int CELL_MARGIN_VERTICAL = 2;
static const int CELL_MARGIN_HORIZONTAL = 2;

static const juce::Colour SELECTED_COLOR(0xffefef80);
static const juce::Colour UNSELECTED_COLOR = juce::Colours::white;

using data::Address;
using data::Value;

TableController::TableController() : TableListBox("TableController") {}

// TODO: can we put this back into the constructor now?
void TableController::initialize(const TableColumnList& c, const char* name) {
  columns_ = c;
  setName(name);
}

void TableController::fillHeader(TableHeaderComponent* headers) {
  Lock l(lock_);
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
  Lock l(lock_);
  g.setColour(rowIsSelected ? SELECTED_COLOR : UNSELECTED_COLOR);
  g.fillRect(0, 0, width, height);
}

void TableController::paintCell(Graphics& g,
                               int rowNumber,
                               int columnId,
                               int width, int height,
                               bool rowIsSelected) {
  Lock l(lock_);
  g.setColour(juce::Colours::black);
  if (columnId > columns_.column_size() || columnId <= 0) {
    LOG(DFATAL) << "columnId " << columnId << " size " << columns_.column_size();
    return;
  }

  const TableColumn& column = columns_.column(columnId - 1);
  String t = displayText(column, rowNumber);
  g.drawText(t, CELL_MARGIN_HORIZONTAL, CELL_MARGIN_VERTICAL,
             width - 2 * CELL_MARGIN_HORIZONTAL,
             height - 2 * CELL_MARGIN_VERTICAL, Justification::centred, true);
}

void TableController::resized() {
  TableHeaderComponent& header = getHeader();
  int columns = header.getNumColumns(false);
  int width = 0;
  int lastC = 0;
  int lastWidth = 0;
  for (int i = 1; i <= columns; ++i) {
    if (header.isColumnVisible(i)) {
      lastC = i;
      lastWidth = header.getColumnWidth(i);
      width += lastWidth;
    }
  }
  if (lastC)
    header.setColumnWidth(lastC, std::max(10, lastWidth + getWidth() - width));


  juce::TableListBox::resized();
  TableController::update();
}

}  // namespace gui
}  // namespace rec
