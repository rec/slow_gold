#include "rec/command/map/CategoryItem.h"

#include "rec/command/map/Editor.h"
#include "rec/command/map/MapItem.h"
#include "rec/command/map/MapItemComponent.h"

namespace rec {
namespace command {

namespace {

const float HEIGHT_RATIO = 0.6f;
const int PADDING = 2;

}  // namespace

CategoryItem::CategoryItem(Editor* editor, const String& name)
    : editor_(editor), categoryName_(name) {
}

void CategoryItem::paintItem(Graphics& g, int width, int height) {
  Font f = g.getCurrentFont();
  f.setHeight(height * HEIGHT_RATIO);
  f.setTypefaceStyle("bold");

  g.setFont(f);
  g.setColour(editor_->findColour(Editor::textColourId));

  g.drawText(categoryName_,
             PADDING, 0, width - PADDING, height,
             Justification::centredLeft, true);
}

}  // namespace command
}  // namespace rec

