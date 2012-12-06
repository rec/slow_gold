#include "rec/command/map/Items.h"
#include "rec/command/map/EditButton.h"
#include "rec/command/map/Editor.h"

namespace rec {
namespace command {

namespace {

const int PADDING = 2;
const float HEIGHT_RATIO = 0.7f;
const int TEXT_X_MARGIN = 4;
const int TEXT_X_OFFSET = 1;
const int TEXT_X_TOTAL = TEXT_X_MARGIN + TEXT_X_OFFSET;
const int TEXT_WIDTH_MAX = 40;
const int TEXT_Y_MARGIN = 1;
const int MAX_NUM_ASSIGNMENTS = 3;  // TODO

}  // namespace

CategoryItem::CategoryItem(const String& n, Component* component)
  : Item(n, "_cat", true), component_(component) {
}

void CategoryItem::paintItem(Graphics& g, int width, int height) {
  Font f = g.getCurrentFont();
  f.setHeight(height * HEIGHT_RATIO);
  f.setTypefaceStyle("bold");
  g.setFont(f);

  g.setColour(component_->findColour(Editor::textColourId));
  g.drawText(name_, PADDING, 0, width - PADDING, height,
             Justification::centredLeft, true);
}

MapItem::MapItem(Editor* editor, CommandID id, const String& name)
    : Item(name, "_id", false), editor_(editor), id_(id) {
}

Component* MapItem::createItemComponent() {
  ptr<Component> c(new MapItemComponent(id_, name_));
  return c.transfer();
}

MapItemComponent::MapItemComponent(CommandID commandID, const String& name)
    : commandID_(commandID), name_(name) {
  setInterceptsMouseClicks (false, true);
  // editor->addChildren(this); // TODO
}

MapItemComponent::~MapItemComponent() {}

void MapItemComponent::createEditButton(const String& desc, int index,
                                        bool isReadOnly, Editor* editor) {
  EditButton* const b = new EditButton(editor, commandID_, desc, index);
  buttons_.add(b);

  b->setEnabled(!isReadOnly);
  b->setVisible(buttons_.size() <= (int) MAX_NUM_ASSIGNMENTS);
  addChildComponent(b);
}

void MapItemComponent::paint(Graphics& g) {
  g.setFont(getHeight() * HEIGHT_RATIO);
  g.setColour(findColour(Editor::textColourId));

  // editor_->getCommandManager()->getNameOfCommand(commandID_), // TODO
  g.drawFittedText(name_,
                   TEXT_X_MARGIN, 0,
                   jmax(TEXT_WIDTH_MAX,
                        getChildComponent(0)->getX() - TEXT_X_TOTAL),
                   getHeight(),
                   Justification::centredLeft, true);
}

void MapItemComponent::resized() {
  int x = getWidth() - TEXT_X_MARGIN;

  for (int i = buttons_.size(); --i >= 0;) {
    EditButton* const b = buttons_.getUnchecked(i);

    b->fitToContent(getHeight() - 2 * TEXT_Y_MARGIN);
    b->setTopRightPosition(x, TEXT_Y_MARGIN);
    x = b->getX() - TEXT_X_TOTAL;
  }
}

}  // namespace command
}  // namespace rec
