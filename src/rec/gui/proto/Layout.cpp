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

std::unique_ptr<Component> makeLayout(const Layout& layout, Component* parent,
                                 const string& oldName) {
  std::unique_ptr<Component> comp;
  auto& constants = juceModel()->constants();
  auto& addr = getProgram()->resizerAddress();
  string name;

  if (layout.has_container()) {
    comp = makeComponent(Context(layout.container(), constants, parent, addr));
    name = layout.container().name();
    name = name.empty() ? oldName : name;
    comp->setName(name);
  } else {
    name = layout.name().empty() ? oldName : layout.name();
    comp.reset(new Panel(name,
                         static_cast<Orientation>(layout.orientation()),
                         layout.resize_other_dimension(),
                         layout.is_main()));
  }
  DCHECK(not name.empty()) << layout.ShortDebugString();
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
    panel->addToPanel(new Panel(name + ".padding"));

  if (layout.has_dimensions()) {
    comp->setSize(constants.getDouble(layout.dimensions().width()),
                  constants.getDouble(layout.dimensions().height()));
  }

  return std::move(comp);
}

}  // namespace

std::unique_ptr<Component> makeLayout(const string& name, Component* parent) {
  std::unique_ptr<Component> comp;
  try {
    comp = makeLayout(program::juceModel()->getLayout(name), parent, name);
  } catch (std::out_of_range&) {
    LOG(DFATAL) << "Can't make layout " << name;
  }
  return std::move(comp);
}

std::unique_ptr<Component> makeLayoutComp(const Context& context) {
  return makeLayout(context.component_.layout(), context.parent_);
}

}  // namespace gui
}  // namespace rec
