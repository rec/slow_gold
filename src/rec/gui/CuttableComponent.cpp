#include "rec/gui/CuttableComponent.h"

using juce::SystemClipboard;

namespace rec {
namespace gui {

CuttableComponent* CuttableComponent::make(Component* comp) {
  return comp->getName().startsWith("cut-") ?
    dynamic_cast<CuttableComponent*>(comp): NULL;
}

bool CuttableComponent::cutToClipboard(Component* comp) {
  if (CuttableComponent* cc = make(comp)) {
    if (cc->canCopy()) {
      SystemClipboard::copyTextToClipboard(cc->cut().c_str());
      return true;
    }
  }
  return false;
}

bool CuttableComponent::copyToClipboard(Component* comp) {
  if (CuttableComponent* cc = make(comp)) {
    if (cc->canCopy()) {
      SystemClipboard::copyTextToClipboard(cc->copy().c_str());
      return true;
    }
  }
  return false;
}

bool CuttableComponent::pasteToClipboard(Component* comp) {
  if (CuttableComponent* cc = make(comp))
    cc->paste(SystemClipboard::getTextFromClipboard().toCString());
  else
    return false;

  return true;
}

}  // namespace gui
}  // namespace rec
