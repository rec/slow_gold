#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/widget/Widget.h"

namespace rec {
namespace widget {
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
}  // namespace widget
}  // namespace rec
