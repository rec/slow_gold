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
  virtual void cut() {}
  virtual bool paste(const string&) const { return false; }
  const string name() const { return ""; }
};

bool cutToClipboard();
bool copyToClipboard();
bool pasteFromClipboard();
bool canCutOrCopy();
bool canPaste();
bool remove();

String cuttableName();

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CUTTABLECOMPONENT__
