#pragma once

#include "rec/gui/Orientation.h"

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

