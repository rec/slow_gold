#include "rec/util/Cuttable.h"

using juce::SystemClipboard;

namespace rec {
namespace util {

Cuttable* Cuttable::current() {
  Component* c = Component::getCurrentlyFocusedComponent();
  if (Cuttable* cuttable = dynamic_cast<Cuttable*>(c))
    return cuttable;

  static Cuttable cuttable;
  return &cuttable;
}

bool Cuttable::cutToClipboard() {
  if (!canCut()) {
    juce::PlatformUtilities::beep();
    return false;
  }

  SystemClipboard::copyTextToClipboard(copy().c_str());
  cut();
  return true;
}

bool Cuttable::copyToClipboard() {
  if (!canCopy()) {
    juce::PlatformUtilities::beep();
    return false;
  }
  SystemClipboard::copyTextToClipboard(copy().c_str());
  return true;
}

bool Cuttable::pasteFromClipboard() {
  if (!canPaste()) {
    juce::PlatformUtilities::beep();
    return false;
  }

  string s(str(SystemClipboard::getTextFromClipboard()));
  if (s.empty()) {
    juce::PlatformUtilities::beep();
    return false;
  }

  paste(s);
  return true;
}

bool Cuttable::remove() {
  if (canCut()) {
    cut();
    return true;
  }

  juce::PlatformUtilities::beep();
  return false;
}

}  // namespace util
}  // namespace rec
