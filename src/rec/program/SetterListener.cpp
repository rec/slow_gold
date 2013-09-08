#include "rec/program/SetterListener.h"

#include "rec/base/make_unique.h"
#include "rec/command/Command.pb.h"
#include "rec/program/JuceModel.h"
#include "rec/program/Program.h"
#include "rec/util/thread/Callback.h"
#include "rec/util/thread/MakeCallback.h"

using namespace rec::command;
using namespace rec::data;

namespace rec {
namespace program {

namespace {

class Selection : public Callback {
  Selection(SetterListener* p, int index) : parent_(p), index_(index) {}
  bool operator()() override {
    parent_->select(index_);
    return true;
  }

  SetterListener* const parent_;
  int const index_;

};

class Toggle : public Callback {
  Toggle(SetterListener* p) : parent_(p) {}
  bool operator()() override {
    parent_->toggle();
    return true;
  }

  SetterListener* const parent_;
};

}  // namespace

SetterListener::SetterListener(const command::Command& command,
                               JuceModel* model)
    : AddressListener(command.setter().address(),
                      command.setter().type_name(),
                      command.setter().is_global() ? GLOBAL_SCOPE : FILE_SCOPE),
      model_(model) {
  Program* pgm = model->program();
  CommandID id = command.command();
  if (command.setter().type() == Setter::TOGGLE) {
    pgm->addCallback(id,
                     unique_ptr<Callback>(thread::methodCallback(this, &SetterListener::toggle)));
  } else {
    for (int i = 0; i < command.index(); ++i) {
      pgm->addCallback(id + i,
                       unique_ptr<Callback>(thread::methodCallback(this, &SetterListener::select, i)));
    }
  }
}

void SetterListener::toggle() {
  {
    Lock l(lock_);
    value_.set_bool_f(not value_.bool_f());
  }
  setValue();
}

void SetterListener::select(int index) {
  {
    Lock l(lock_);
    value_.set_uint32_f(index);
  }
  setValue();
}

void SetterListener::operator()(const Value& v) {
  {
    Lock l(lock_);
    value_ = v;
  }
  model_->menuItemsChanged();
}

void SetterListener::setValue() {
  AddressListener::setValue(value_);
  model_->menuItemsChanged();
}

}  // namespace program
}  // namespace rec

