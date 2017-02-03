#include <gtest/gtest.h>

#include "rec/widget/status/TextComponent.h"

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
