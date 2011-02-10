#include "rec/gui/CutAndPaste.h"
#include "rec/gui/CuttableComponent.h"

using juce::SystemClipboard;

namespace rec {
namespace gui {

static CuttableComponent* make() {
  Component* comp = Component::getCurrentlyFocusedComponent();

  return comp && comp->getName().startsWith("cut-") ?
    dynamic_cast<CuttableComponent*>(comp): NULL;
}

bool canCutOrCopy() {
  if (CuttableComponent* cc = make())
    return cc->canCopy();
  else
    return false;
}

bool canPaste() {
  if (CuttableComponent* cc = make())
    return cc->canCopy();
  else
    return false;
}

bool cutToClipboard() {
  if (CuttableComponent* cc = make()) {
    if (cc->canCopy()) {
      SystemClipboard::copyTextToClipboard(cc->cut().c_str());
      return true;
    }
  }

  juce::PlatformUtilities::beep();
  return false;
}

bool copyToClipboard() {
  if (CuttableComponent* cc = make()) {
    if (cc->canCopy()) {
      SystemClipboard::copyTextToClipboard(cc->copy().c_str());
      return true;
    }
  }

  juce::PlatformUtilities::beep();
  return false;
}

bool pasteFromClipboard() {
  if (CuttableComponent* cc = make()) {
    cc->paste(SystemClipboard::getTextFromClipboard().toCString());
    return true;
  }

  juce::PlatformUtilities::beep();
  return false;
}

bool deleteKeepingClipboard() {
  if (CuttableComponent* cc = make()) {
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
