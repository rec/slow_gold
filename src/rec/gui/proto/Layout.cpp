#include "rec/gui/proto/Layout.h"
#include "rec/gui/proto/Layout.pb.h"
#include "rec/gui/proto/Panel.h"
#include "rec/program/JuceModel.h"

namespace rec {
namespace gui {

namespace {

unique_ptr<Component> makeLayout(const Layout& layout) {
  unique_ptr<Panel> panel;

  return unique_ptr<Component>(panel.release());
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
