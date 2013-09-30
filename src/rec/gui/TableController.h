#ifndef __REC_GUI_TABLEMODELBASE__
#define __REC_GUI_TABLEMODELBASE__

#include "rec/gui/DisableableComponent.h"
#include "rec/base/SampleTime.h"
#include "rec/gui/TableColumn.pb.h"
#include "rec/data/Address.h"

namespace rec {
namespace gui {

class TableController : public TableListBoxModel, public TableListBox,
                        public DisableableComponent {
 public:
  TableController();

  void initialize(const TableColumnList& columns, const char* name);

  virtual void fillHeader(TableHeaderComponent* headers);
  virtual void paintRowBackground(Graphics& g,
                                  int row,
                                  int width, int height,
                                  bool isRowSelected);
  virtual void paintCell(Graphics& g,
                         int row, int column,
                         int width, int height,
                         bool isRowSelected);

  void updateAndRepaint() { update(); repaint(); }
  const TableColumnList& columns() { return columns_; }
  virtual void resized();

  virtual Component* refreshComponentForCell(int row, int columnId,
                                             bool isRowSelected,
                                             Component* componentToUpdate);

  virtual void setFieldValue(int row, int column, const String& text) = 0;
  virtual String displayText(int col, int row) const = 0;

  virtual String getCellTooltip(int row, int column) const = 0;
  bool editable(int col) const;
  virtual bool selected(int row) const = 0;
  virtual void setEditing(bool) {}

 protected:
  virtual void update() { updateContent(); }

  ptr<Message> message_;
  TableColumnList columns_;
  CriticalSection lock_;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(TableController);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TABLEMODELBASE__
