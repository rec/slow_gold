#include "rec/gui/proto/Help.h"
#include "rec/gui/proto/Component.pb.h"
#include "rec/gui/proto/Constants.h"
#include "rec/gui/proto/Context.h"
#include "rec/gui/proto/Panel.h"
#include "rec/gui/SimpleLabel.h"
#include "rec/util/Binary.h"

using namespace juce;

namespace rec {
namespace gui {

namespace {

class HelpPanel : public Panel {
 public:
  HelpPanel(const Context& context) {
    auto& comp = context.component_;
    auto& constants = context.constants_;
    const HelpProto& proto = comp.help();
    addToPanel(&helpCaption_, constants, comp.size(), proto.caption_size());
    addToPanel(&helpBody_, constants, comp.size(), proto.body_size());
    INSTANCE = this;

    // TODO: font here!
    // TODO: make sure that we are the one getting help updates automatically!
  }

  void setTooltip(const String& tt) override {
    helpCaption_.setTooltip(tt);
    helpBody_.setTooltip(tt);
  }

  void setHelp(const Tooltip& tt) {
    helpCaption_.setTextIfChanged(tt.first, juce::dontSendNotification);
    helpBody_.setTextIfChanged(tt.second, juce::dontSendNotification);
  }

  ~HelpPanel() {
    INSTANCE = nullptr;
  }

  static HelpPanel* INSTANCE;

  SimpleLabel helpCaption_;
  SimpleLabel helpBody_;
};

HelpPanel* HelpPanel::INSTANCE = nullptr;

}  // namespace

unique_ptr<Component> makeHelp(const Context& context) {
  return unique_ptr<Component>(new HelpPanel(context));
}

void setHelp(const Tooltip& tt) {
  HelpPanel::INSTANCE->setHelp(tt);
}

}  // namespace gui
}  // namespace rec

