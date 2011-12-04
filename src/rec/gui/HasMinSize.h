#ifndef __REC_GUI_HASMINSIZE__
#define __REC_GUI_HASMINSIZE__

#include "rec/base/base.h"

namespace rec {
namespace gui {

class HasMinSize {
 public:
  HasMinSize() {}
  virtual ~HasMinSize() {}
  
  virtual juce::Point<int> getMinSize() const = 0;

 private:
  DISALLOW_COPY_ASSIGN_AND_LEAKS(HasMinSize);
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_HASMINSIZE__
