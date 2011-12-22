#include "rec/gui/GuiWriteable.h"

namespace rec {
namespace gui {

namespace {

static int64 time() { return juce::Time::currentTimeMillis(); }

typedef std::vector<GuiWriteable*> WriteableVector;

WriteableVector* getWriteableVector() {
  static WriteableVector v;
  return &v;
}

}  // namespace

void GuiWriteable::add(GuiWriteable* writeable) {
  getWriteableVector()->push_back(writeable);
}

void GuiWriteable::writeAll() {
  WriteableVector* v = getWriteableVector();
  for (WriteableVector::const_iterator i = v->begin(); i != v->end(); ++i)
    (*i)->writeGui();
}

void GuiWriteable::writeGui() {
  Lock l(lock_);
  if (needsUpdate_ && (time() - lastUpdateTime_) > MIN_UPDATE_GAP) {
    doWriteGui();
    needsUpdate_ = false;
  }
}

void GuiWriteable::requestWrite() {
  Lock l(lock_);

  needsUpdate_ = true;
  lastUpdateTime_ = time();
}

}  // namespace gui
}  // namespace rec
