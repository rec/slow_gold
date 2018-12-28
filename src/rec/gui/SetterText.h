#pragma once

#include "rec/data/Value.h"
#include "rec/gui/CaptionText.h"
#include "rec/data/AddressListener.h"

namespace rec {
namespace gui {

class SetterText : public CaptionText, public data::AddressListener {
  public:
    SetterText(const String& name,
               const data::Address& address,
               const String& tip = {},
               const String& caption = {},
               bool useCaption = true,
               int captionSize = CAPTION_SIZE);
    ~SetterText() override {}

    void operator()(const data::Value& v) override;
    void textEditorTextChanged(TextEditor&) override;

  private:
    DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(SetterText);
};

}  // namespace gui
}  // namespace rec
