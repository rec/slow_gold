#ifndef __REC_WIDGET_WAVEFORM_OUTLINEDCURSORLABEL__
#define __REC_WIDGET_WAVEFORM_OUTLINEDCURSORLABEL__

#include "rec/gui/SimpleLabel.h"

namespace rec {
namespace widget {
namespace waveform {

class Cursor;

class OutlinedCursorLabel : public gui::SimpleLabel {
 public:
  explicit OutlinedCursorLabel(Cursor *cursor) : cursor_(cursor) {}
  virtual ~OutlinedCursorLabel() {}

  virtual void paint(Graphics&);

  Cursor* getCursor() const { return cursor_; }

 private:
  Cursor* cursor_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(OutlinedCursorLabel);
};

}  // namespace waveform
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_WAVEFORM_OUTLINEDCURSORLABEL__
