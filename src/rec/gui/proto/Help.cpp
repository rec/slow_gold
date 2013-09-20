#include "rec/gui/proto/Help.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Panel.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/util/Binary.h"

using namespace juce;

namespace rec {
namespace gui {

namespace {

class HelpPanel : public Panel {
 public:
  HelpPanel(const ComponentProto& comp, const Constants& constants) {
    const HelpProto& proto = comp.help();
    addToPanel(&helpCaption_, constants, comp.size(), proto.caption_size());
    addToPanel(&helpBody_, constants, comp.size(), proto.body_size());

    // TODO: make sure that we are the one getting help updates automatically!
  }

  void setTooltip(const String& newTooltip) override {
    Panel::setTooltip(newTooltip);
    helpCaption_.setTooltip(newTooltip);
    helpBody_.setTooltip(newTooltip);
  }

 private:
  SimpleLabel helpCaption_;
  SimpleLabel helpBody_;
};

}  // namespace

unique_ptr<Component> makeHelp(const ComponentProto& proto,
                               const Constants& constants) {
  return unique_ptr<Component>(new HelpPanel(proto, constants));
}

}  // namespace gui
}  // namespace rec
