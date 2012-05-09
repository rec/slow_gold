#include "rec/util/Cuttable.h"

using juce::SystemClipboard;

namespace rec {
namespace util {

namespace {

class EmptyCuttable : public Cuttable {
 public:
  virtual bool canCopy() const { return false; }
  virtual bool canCut() const { return false; }
  virtual bool canPaste(const string&) const { return false; }
  virtual bool paste(const string&) { return false;  }
  virtual const string cuttableName() const { return ""; }
  virtual string copy() const { return ""; }
  virtual void cut() {}
};

static EmptyCuttable EMPTY;
static HasCuttable* DEFAULT_CUTTABLE = &EMPTY;

Cuttable* current() {
  Component* c = Component::getCurrentlyFocusedComponent();
  if (HasCuttable* cuttable = dynamic_cast<Cuttable*>(c))
    return cuttable->cuttable();

  return DEFAULT_CUTTABLE->cuttable();
}

}  // namespace

bool cutToClipboard() {
  Cuttable* c = current();
  if (!c->canCut()) {
    beep();
    return false;
  }

  SystemClipboard::copyTextToClipboard(str(c->copy()));
  c->cut();
  return true;
}

bool copyToClipboard() {
  Cuttable* c = current();
  if (!c->canCopy()) {
    beep();
    return false;
  }
  SystemClipboard::copyTextToClipboard(str(c->copy()));
  return true;
}

bool pasteFromClipboard() {
  Cuttable* c = current();
  string s(str(SystemClipboard::getTextFromClipboard()));
  if (!c->canPaste(s)) {
    beep();
    return false;
  }

  c->paste(s);
  return true;
}

bool cutNoClipboard() {
  Cuttable* c = current();
  if (c->canCut()) {
    c->cut();
    DLOG(INFO) << "yes!";
    return true;
  }

  beep();
  DLOG(INFO) << "no!";
  return false;
}

bool canCopy() {
  return current()->canCopy();
}

bool canCut() {
  return current()->canCut();
}

bool canPaste() {
  return current()->canPaste(str(SystemClipboard::getTextFromClipboard()));
}

const string cuttableName() {
  return current()->cuttableName();
}

void setDefaultCuttable(HasCuttable* c) {
  DEFAULT_CUTTABLE = c;
}

}  // namespace util
}  // namespace rec
