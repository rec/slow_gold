#ifndef __REC_GUI_HASSIZEHINTS__
#define __REC_GUI_HASSIZEHINTS__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class HasSizeHints {
 public:
  enum Hint { MIN, MAX, PREF, LAST };

  HasSizeHints() {}
  virtual ~HasSizeHints() {}

  virtual Orientation orientation() const = 0;
  virtual int size(Hint) const = 0;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(HasSizeHints);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_HASSIZEHINTS__
