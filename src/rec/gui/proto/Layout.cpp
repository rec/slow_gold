#include "rec/gui/proto/Layout.h"
#include "rec/gui/proto/Layout.pb.h"
#include "rec/gui/proto/Component.h"
#include "rec/gui/proto/Panel.h"
#include "rec/program/JuceModel.h"

using namespace rec::program;

namespace rec {
namespace gui {

namespace {

unique_ptr<Component> makeLayout(const Layout& layout) {
  unique_ptr<Component> result;
  const Constants& constants = juceModel()->constants();
  if (layout.has_container()) {
    result = makeComponent(layout.container(), constants);
  } else {
    result.reset(new Panel(str(layout.name()),
                           static_cast<Orientation>(layout.orientation()),
                           layout.resize_other_dimension(),
                           layout.is_main(),
                           true));
  }
  Panel* panel = dynamic_cast<Panel*>(result.get());

  for (auto& component: layout.component()) {
    Component* child = makeComponent(component, constants).release();
    if (panel)
      panel->addToPanel(child, constants, layout.size(), component.size());
    else
      result->addAndMakeVisible(child);  // leaks memory here.
  }

  return std::move(result);
}

}  // namespace

unique_ptr<Component> makeLayout(const string& name) {
  unique_ptr<Component> result;
  try {
    result = makeLayout(program::juceModel()->getLayout(name));
  } catch (std::out_of_range&) {
    LOG(DFATAL) << "Can't make layout " << name;
  }
  return std::move(result);
}

}  // namespace gui
}  // namespace rec
