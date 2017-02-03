#pragma once

#include "rec/base/base.h"

namespace rec { namespace data { class Address; }}

namespace rec {
namespace gui {

class ComponentProto;
class Constants;
class ComponentProto;

struct Context {
    Context(const ComponentProto& component,
                    const Constants& constants,
                    Component* parent,
                    const data::Address& address)
            : component_(component),
                constants_(constants),
                parent_(parent),
                address_(address) {
    }

    const ComponentProto& component_;
    const Constants& constants_;
    Component* parent_;
    const data::Address& address_;
};

}  // namespace gui
}  // namespace rec

