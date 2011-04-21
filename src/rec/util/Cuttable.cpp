#include "rec/util/Cuttable.h"

using juce::SystemClipboard;

namespace rec {
namespace util {

static Cuttable* make() {
  Component* comp = Component::getCurrentlyFocusedComponent();

  return comp && comp->getName().startsWith("cut-") ?
    dynamic_cast<Cuttable*>(comp): NULL;
}

bool canCutOrCopy() {
  if (Cuttable* cc = make())
    return cc->canCopy();
  else
    return false;
}

bool canPaste() {
  if (!SystemClipboard::getTextFromClipboard().length())
    return false;

  else if (Cuttable* cc = make())
    return cc->canPaste();

  else
    return false;
}

bool cutToClipboard() {
  if (Cuttable* cc = make()) {
    if (cc->canCopy()) {
      SystemClipboard::copyTextToClipboard(cc->copy().c_str());
      cc->cut();
      return true;
    }
  }

  juce::PlatformUtilities::beep();
  return false;
}

bool copyToClipboard() {
  if (Cuttable* cc = make()) {
    if (cc->canCopy()) {
      SystemClipboard::copyTextToClipboard(cc->copy().c_str());
      return true;
    }
  }

  juce::PlatformUtilities::beep();
  return false;
}

bool pasteFromClipboard() {
  if (Cuttable* cc = make()) {
    string s(str(SystemClipboard::getTextFromClipboard()));
    if (s.empty())
      return false;

    cc->paste(s);
    return true;
  }

  juce::PlatformUtilities::beep();
  return false;
}

bool remove() {
  if (Cuttable* cc = make()) {
    if (cc->canCopy()) {
      cc->cut();
      return true;
    }
  }

  juce::PlatformUtilities::beep();
  return false;
}

}  // namespace util
}  // namespace rec
