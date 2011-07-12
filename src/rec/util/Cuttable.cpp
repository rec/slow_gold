#include "rec/util/Cuttable.h"

using juce::SystemClipboard;

namespace rec {
namespace util {

namespace {

class EmptyCuttable : public Cuttable {
 public:
  virtual bool canCopy() const { return false; }
  virtual bool canCut() const { return false; }
  virtual bool canPaste() const { return false; }
  virtual bool paste(const string&) { return false;  }
  virtual const string cuttableName() const { return ""; }
  virtual string copy() const { return ""; }
  virtual void cut() {}
};

Cuttable* current() {
  Component* c = Component::getCurrentlyFocusedComponent();
  if (Cuttable* cuttable = dynamic_cast<Cuttable*>(c))
    return cuttable;

  static EmptyCuttable empty;
  return &empty;
}

}  // namespace

bool cutToClipboard() {
  Cuttable* c = current();
  if (!c->canCut()) {
    juce::PlatformUtilities::beep();
    return false;
  }

  SystemClipboard::copyTextToClipboard(str(c->copy()));
  c->cut();
  return true;
}

bool copyToClipboard() {
  Cuttable* c = current();
  if (!c->canCopy()) {
    juce::PlatformUtilities::beep();
    return false;
  }
  SystemClipboard::copyTextToClipboard(str(c->copy()));
  return true;
}

bool pasteFromClipboard() {
  Cuttable* c = current();
  if (!c->canPaste()) {
    juce::PlatformUtilities::beep();
    return false;
  }

  string s(str(SystemClipboard::getTextFromClipboard()));
  if (s.empty()) {
    juce::PlatformUtilities::beep();
    return false;
  }

  c->paste(s);
  return true;
}

bool cutNoClipboard() {
  Cuttable* c = current();
  if (c->canCut()) {
    c->cut();
    return true;
  }

  juce::PlatformUtilities::beep();
  return false;
}

bool canCopy() { 
  return current()->canCopy(); 
}
bool canCut() { return current()->canCut(); }
bool canPaste() { return current()->canPaste(); }

const string cuttableName() { return current()->cuttableName(); }

}  // namespace util
}  // namespace rec
