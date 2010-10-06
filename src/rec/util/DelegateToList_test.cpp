#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/util/DelegateToList.h"

#include "rec/base/ArraySize.h"
#include "rec/gui/Component.pb.h"

namespace rec {
namespace util {
namespace {

using gui::ComponentDesc;
using gui::color::Colors;
using gui::FontDesc;

TEST(DelegateToList, All) {
  ComponentDesc c1;
  ComponentDesc c2;
  ComponentDesc c3;
  ComponentDesc c4;

  c1.mutable_colors()->add_color()->set_rgb(12345);
  c2.mutable_font()->set_name("some font");
  c3.set_margin(5);
  c4.set_transparent(false);

  ComponentDesc* begin[] = {&c1, &c2, NULL, &c2, &c3, &c4};
  ComponentDesc** end = begin + arraysize(begin);

  const Colors& colors = delegateToList(&ComponentDesc::colors,
                                        &ComponentDesc::has_colors,
                                        begin, end, Colors());
  EXPECT_EQ(12345, colors.color(0).rgb());

  const FontDesc& font = delegateToList(&ComponentDesc::font,
                                        &ComponentDesc::has_font,
                                        begin, end, FontDesc());
  EXPECT_EQ("some font", font.name());

  EXPECT_EQ(5, delegateToList(&ComponentDesc::margin,
                              &ComponentDesc::has_margin,
                              begin, end, 0));

  EXPECT_EQ(false, delegateToList(&ComponentDesc::transparent,
                                  &ComponentDesc::has_transparent,
                                  begin, end, true));
}

}  // namespace
}  // namespace util
}  // namespace rec
