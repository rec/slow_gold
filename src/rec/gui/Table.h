#ifndef __REC_GUI_TABLE__
#define __REC_GUI_TABLE__

#include "rec/data/persist/Persist.h"

namespace rec {
namespace gui {

template <typename Proto>
class Table : public juce::TableListBoxModel, public DataListener<Proto> {
 public:
  Table(const Address& address) : address_(address) {}

  int getNumRows() {

  }

  virtual void paintRowBackground (Graphics& g,
                                     int rowNumber,
                                     int width, int height,
                                     bool rowIsSelected) = 0;

    /** This must draw one of the cells.

        The graphics context's origin will already be set to the top-left of the cell,
        whose size is specified by (width, height).
    */
    virtual void paintCell (Graphics& g,
                            int rowNumber,
                            int columnId,
                            int width, int height,
                            bool rowIsSelected) = 0;
  void get() {
  }

 private:
  const Address address_;

  DISALLOW_COPY_ASSIGN_AND_EMPTY(Table);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_TABLE__
