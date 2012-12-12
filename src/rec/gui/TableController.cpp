#include "rec/gui/TableController.h"
#include "rec/data/Value.h"
#include "rec/util/thread/CallAsync.h"
#include "rec/util/Copy.h"
#include "rec/gui/SimpleLabel.h"

namespace rec {
namespace gui {

static const int CELL_MARGIN_VERTICAL = 2;
static const int CELL_MARGIN_HORIZONTAL = 2;
static const int VERTICAL_SCROLL_WIDTH = 20;

static const juce::Colour SELECTED_COLOR(0xffefef80);
static const juce::Colour UNSELECTED_COLOR = juce::Colours::white;

TableController::TableController() : TableListBox("TableController") {}

void TableController::initialize(const TableColumnList& c, const char* name) {
  // This can't be part of the constructor, because the constructor might want
  // to create the TableColumnList.
  columns_ = c;
  setName(name);
}

void TableController::fillHeader(TableHeaderComponent* headers) {
  Lock l(lock_);
  for (int i = 0; i < columns_.column_size(); ++i)  {
    const TableColumn& col = columns_.column(i);
    int columnId = i + 1;  // Juce doesn't allow column IDs of 0, so add 1.
    headers->addColumn(str(col.name()), columnId,
                       col.width(), col.minimum_width(), col.maximum_width(),
                       col.property_flags());
  }
}

void TableController::paintRowBackground(Graphics& g,
                                        int row,
                                        int width, int height,
                                        bool rowIsSelected) {
  Lock l(lock_);
  g.setColour(selected(row) ? SELECTED_COLOR : UNSELECTED_COLOR);
  g.fillRect(0, 0, width, height);
}

void TableController::paintCell(Graphics& g,
                               int row,
                               int columnId,
                               int width, int height,
                               bool /*rowIsSelected*/) {
  g.setColour(juce::Colours::black);
  int column = columnId - 1;

  Lock l(lock_);
  if (column >= columns_.column_size() || column < 0)
    LOG(DFATAL) << "column " << column << ", size " << columns_.column_size();

  String t = displayText(column, row);
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

  if (lastC) {
    int newWidth = lastWidth + getWidth() - width;
    if (getViewport()->getVerticalScrollBar()->isVisible())
      newWidth -= getViewport()->getScrollBarThickness();

    header.setColumnWidth(lastC, std::max(10, newWidth));
  }

  juce::TableListBox::resized();
  update();
}


bool TableController::editable(int col) const {
  Lock l(lock_);
  return ((columns_.column(col).property_flags() & TableColumn::EDITABLE) != 0);
}

class TableLabel : public SimpleLabel {
 public:
  explicit TableLabel(TableController* table, int col, int row)
      : SimpleLabel("TableLabel " + String(col) + "-" + String(row)),
        table_(table), col_(col), row_(row) {
    setEditable(table->editable(col), false, false);
    setJustificationType(Justification::centredLeft);
  }

  void setEditorBackground(const juce::Colour& c) {
    setColour(juce::Label::backgroundColourId, c);
  }

  virtual void textEditorTextChanged(TextEditor&) {
    table_->setFieldValue(col_, row_, getText(true));
  }

  void setText(const String& s) {
    if (s != getText(true))
      SimpleLabel::setText(s, false);
  }

  virtual void editorShown(TextEditor*) {
    table_->setEditing(true);
  }

  virtual void editorAboutToBeHidden(TextEditor*) {
    table_->setEditing(false);
  }

  TableController* const table_;
  int col_;
  int row_;

 private:
  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(TableLabel);
};

Component* TableController::refreshComponentForCell(int row, int columnId,
                                                    bool isRowSelected,
                                                    Component* existing) {
  int column = columnId - 1;  // To account for the 1 we added above.
  TableLabel* text = dynamic_cast<TableLabel*>(existing);
  if (!text) {
    DCHECK(!existing);
    if (!editable(column))
      return NULL;
    text = new TableLabel(this, column, row);
  } else {
    text->col_ = column;
    text->row_ = row;
    DCHECK_EQ(column, text->col_);
    DCHECK_EQ(row, text->row_);
  }

  String s = displayText(column, row);
  text->setText(s);
  text->setTooltip(getCellTooltip(column, row));
  text->setEditorBackground(selected(row) ? SELECTED_COLOR :
                              UNSELECTED_COLOR);

  return text;
}

}  // namespace gui
}  // namespace rec
