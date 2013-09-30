#include "rec/gui/proto/Layout.h"
#include "rec/gui/proto/Component.h"
#include "rec/gui/proto/Context.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Layout.pb.h"
#include "rec/gui/proto/Panel.h"
#include "rec/program/JuceModel.h"
#include "rec/program/Program.h"

using namespace rec::program;

namespace rec {
namespace gui {

namespace {

unique_ptr<Component> makeLayout(const Layout& layout, Component* parent) {
  unique_ptr<Component> comp;
  auto& constants = juceModel()->constants();
  auto& addr = getProgram()->resizerAddress();

  if (layout.has_container()) {
    comp = makeComponent(Context(layout.container(), constants, parent, addr));
    comp->setName(layout.container().name());
    DLOG(INFO) << layout.container().name();
    // comp->setTooltip(layout.container().tooltip()); // TODO:
  } else {
    comp.reset(new Panel(str(layout.name()),
                           static_cast<Orientation>(layout.orientation()),
                           layout.resize_other_dimension(),
                           layout.is_main()));
  }
  Panel* panel = dynamic_cast<Panel*>(comp.get());
  for (auto& component: layout.component()) {
    auto child = makeComponent(Context(component, constants, panel, addr));
    if (panel) {
      auto& size = component.has_size() ? component.size() :
          layout.default_size();
      panel->addToPanel(child.get(), constants, size);
    } else {
      comp->addAndMakeVisible(child.get());
    }
    child.release();
  }

  if (layout.has_padding())
    panel->addToPanel(new Panel);

  if (layout.has_dimensions()) {
    comp->setSize(constants.getDouble(layout.dimensions().width()),
                  constants.getDouble(layout.dimensions().height()));
  }

  return std::move(comp);
}

}  // namespace

unique_ptr<Component> makeLayout(const string& name, Component* parent) {
  unique_ptr<Component> comp;
  try {
    comp = makeLayout(program::juceModel()->getLayout(name), parent);
  } catch (std::out_of_range&) {
    LOG(DFATAL) << "Can't make layout " << name;
  }
  return std::move(comp);
}

unique_ptr<Component> makeLayoutComp(const Context& context) {
  return makeLayout(context.component_.layout(), context.parent_);
}

}  // namespace gui
}  // namespace rec
