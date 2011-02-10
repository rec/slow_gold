#include "rec/gui/CutAndPaste.h"
#include "rec/util/Cuttable.h"

using juce::SystemClipboard;

namespace rec {
namespace gui {

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
  if (Cuttable* cc = make())
    return cc->canCopy();
  else
    return false;
}

bool cutToClipboard() {
  if (Cuttable* cc = make()) {
    if (cc->canCopy()) {
      SystemClipboard::copyTextToClipboard(cc->cut().c_str());
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
    cc->paste(SystemClipboard::getTextFromClipboard().toCString());
    return true;
  }

  juce::PlatformUtilities::beep();
  return false;
}

bool deleteKeepingClipboard() {
  if (Cuttable* cc = make()) {
    if (cc->canCopy()) {
      cc->cut();
      return true;
    }
  }

  juce::PlatformUtilities::beep();
  return false;
}


}  // namespace gui
}  // namespace rec
