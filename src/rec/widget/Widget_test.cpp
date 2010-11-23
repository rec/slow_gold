#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/widget/status/Time.h"

namespace rec {
namespace widget {
namespace {

TEST(Widget, someMethod) {
  // Just make sure it compiles.
  juce::MessageManager::getInstance();
  status::time::TextComponent widget(status::time::Text());
}

}  // namespace
}  // namespace widget
}  // namespace rec
