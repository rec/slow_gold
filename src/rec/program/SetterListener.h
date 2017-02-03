#pragma once

#include "rec/data/AddressListener.h"
#include "rec/data/Value.h"

namespace rec { namespace command { class Command; }}

namespace rec {
namespace program {

class JuceModel;

class SetterListener : public data::AddressListener {
 public:
  SetterListener(CommandID, const command::Command&, JuceModel*);

  void toggle();
  void select(int index);
  void operator()(const data::Value& v) override;

 private:
  void setValue();

  data::Value value_;  // TODO: move to AddressListener.
  JuceModel* const model_;
  CriticalSection lock_;

  DISALLOW_COPY_ASSIGN_EMPTY_AND_LEAKS(SetterListener);
};

}  // namespace program
}  // namespace rec


