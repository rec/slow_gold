#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/widget/tree/Directory.h"

using namespace juce;

namespace rec {
namespace widget {
namespace tree {
namespace {

TEST(Directory, All) {
#if 0
  {
    MessageManagerLock l(Thread::getCurrentThread());
    LookAndFeel::setDefaultLookAndFeel(NULL);
  }
#endif
  Directory d(NodeDesc(), ShadowFile(File("~/iTunes"), File("~/iTunes")));
  d.computeChildren();
  d.setOpen(true);

  for (int i = 0; i < d.getNumSubItems(); ++i)
    LOG(INFO) << ((Node*) d.getSubItem(i))->name();
}

}  // namespace
}  // namespace tree
}  // namespace widget
}  // namespace rec
