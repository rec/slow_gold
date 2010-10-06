#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/widgets/Widget.h"

namespace rec {
namespace widgets {
namespace {

class WidgetTest : public WidgetBase<Component> {
 public:
  WidgetTest() : WidgetBase<Component>(WidgetDesc()) {}
  virtual void doPaint(Graphics& g, const Rectangle<int>& bounds) {}
};

TEST(Widget, someMethod) {
  // Just make sure it compiles.
  MessageManager::getInstance();
  WidgetTest widget;
}

}  // namespace
}  // namespace widgets
}  // namespace rec
