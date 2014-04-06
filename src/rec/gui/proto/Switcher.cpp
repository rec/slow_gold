#include <tuple>

#include "rec/gui/proto/Switcher.h"

#include "rec/data/AddressListener.h"
#include "rec/gui/proto/Context.h"
#include "rec/gui/ApplyRecursive.h"
#include "rec/gui/proto/Panel.h"
#include "rec/program/Program.h"
#include "rec/program/JuceModel.h"
#include "rec/util/Binary.h"

using namespace juce;
using namespace rec::data;

namespace rec {
namespace gui {

namespace {

struct Part {
  double min_;
  double max_;
  double pref_;

  unique_ptr<Component> component_;
};

void layoutRepaint(Component* comp) {
  if (Panel* panel = dynamic_cast<Panel*>(comp))
    panel->layout();
  else
    comp->repaint();
}

class Switcher : public Panel, public AddressListener {
 public:
  explicit Switcher(const Context& context)
  : Panel(context.component_.name()),
    AddressListener(context.component_.address()),
    index_(-1) {
  }

  void operator()(const data::Value& value) override {
    int index;
    if (value.has_bool_f())
      index = value.bool_f();
    else if (value.has_enum_f())
      index = value.enum_f();

    if (index == index_)
      return;
    index_ = index;
    MessageManagerLock l;
    for (auto i = 0; i < getNumChildComponents(); ++i)
      getChildComponent(i)->setVisible(i == index_);
  }

  void layout() override {
    auto bounds = getLocalBounds();
    for (auto i = 0; i < getNumChildComponents(); ++i)
      getChildComponent(i)->setBounds(bounds);
    repaint();
  }

 private:
  int index_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Switcher);
};

}  // namespace

unique_ptr<Component> makeSwitcher(const Context& context) {
  return unique_ptr<Component>(new Switcher(context));
}

}  // namespace gui
}  // namespace rec
