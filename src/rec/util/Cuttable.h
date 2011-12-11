#ifndef __REC_UTIL_CUTTABLECOMPONENT__
#define __REC_UTIL_CUTTABLECOMPONENT__

#include "rec/util/Listener.h"

namespace rec {
namespace util {

bool cutToClipboard();
bool copyToClipboard();
bool pasteFromClipboard();
bool cutNoClipboard();
bool canCopy();
bool canCut();
bool canPaste();
const string cuttableName();

class Cuttable;

class HasCuttable {
 public:
  HasCuttable() {}
  virtual ~HasCuttable() {}
  virtual Cuttable* cuttable() = 0;
};

class Cuttable : public HasCuttable {
 public:
  Cuttable() {}
  virtual ~Cuttable() {}

  virtual Cuttable* cuttable() { return this; }

  virtual bool canCopy() const = 0;
  virtual bool canCut() const = 0;
  virtual bool canPaste() const = 0;
  virtual bool paste(const string&) = 0;
  virtual const string cuttableName() const = 0;
  virtual string copy() const = 0;
  virtual void cut() = 0;
};

void setDefaultCuttable(HasCuttable*);


}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_CUTTABLECOMPONENT__
