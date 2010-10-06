#include <gtest/gtest.h>
#include <glog/logging.h>

#include "rec/util/DelegateToList.h"

#include "rec/base/ArraySize.h"
#include "rec/widget/Widget.pb.h"

namespace rec {
namespace util {
namespace {

using widget::Widget;
using gui::Colors;
using gui::FontDesc;

TEST(DelegateToList, All) {
  Widget c1;
  Widget c2;
  Widget c3;
  Widget c4;

  c1.mutable_colors()->add_color()->set_rgb(12345);
  c2.mutable_font()->set_name("some font");
  c3.set_margin(5);
  c4.set_transparent(false);

  Widget* begin[] = {&c1, &c2, NULL, &c2, &c3, &c4};
  Widget** end = begin + arraysize(begin);

  const Colors& colors = delegateToList(&Widget::colors,
                                        &Widget::has_colors,
                                        begin, end, Colors());
  EXPECT_EQ(12345, colors.color(0).rgb());

  const FontDesc& font = delegateToList(&Widget::font,
                                        &Widget::has_font,
                                        begin, end, FontDesc());
  EXPECT_EQ("some font", font.name());

  EXPECT_EQ(5, delegateToList(&Widget::margin,
                              &Widget::has_margin,
                              begin, end, 0));

  EXPECT_EQ(false, delegateToList(&Widget::transparent,
                                  &Widget::has_transparent,
                                  begin, end, true));
}

}  // namespace
}  // namespace util
}  // namespace rec
