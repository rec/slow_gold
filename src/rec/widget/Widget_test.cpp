#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/widget/Time.h"

namespace rec {
namespace widget {
namespace {

TEST(Widget, someMethod) {
  // Just make sure it compiles.
  juce::MessageManager::getInstance();
  time::TextComponent widget(time::Text());
}

}  // namespace
}  // namespace widget
}  // namespace rec
