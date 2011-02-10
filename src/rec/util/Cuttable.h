#ifndef __REC_UTIL_CUTTABLECOMPONENT__
#define __REC_UTIL_CUTTABLECOMPONENT__

#include "rec/base/base.h"

namespace rec {
namespace util {

class Cuttable  {
 public:
  Cuttable() {}
  virtual ~Cuttable() {}
  virtual bool canCopy() const { return false; }
  virtual bool canPaste() const { return false; }
  virtual string copy() const { return ""; }
  virtual string cut() { return ""; }
  virtual bool paste(const string&) const { return false; }
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CUTTABLECOMPONENT__
