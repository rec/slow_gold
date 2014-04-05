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

  ~Switcher() {
    removeAllChildren();
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
    removeAllChildren();

    MessageManagerLock l;
    auto& p = parts_[index];
    Panel::addToPanel(p.component_.get(), p.min_, p.max_, p.pref_);
    DLOG(INFO) << p.component_->getNumChildComponents();
    applyRecursiveDepthFirst(&layoutRepaint, this);
  }

  void addToPanel(Component* c, double min, double max, double pref) override {
    Part part;
    part.component_.reset(c);
    part.min_ = min;
    part.max_ = max;
    part.pref_ = pref;

    parts_.push_back(std::move(part));
  }

 private:
  vector<Part> parts_;
  int index_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(Switcher);
};

}  // namespace

unique_ptr<Component> makeSwitcher(const Context& context) {
  return unique_ptr<Component>(new Switcher(context));
}

}  // namespace gui
}  // namespace rec
