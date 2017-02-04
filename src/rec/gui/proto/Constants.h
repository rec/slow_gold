#pragma once

#include <unordered_map>

#include "rec/base/base.h"

namespace rec {
namespace gui {

class ConstantProtos;

class Constants {
  public:
    using ComponentMaker = std::unique_ptr<Component> (*)(const string&);

    Constants() {}
    Constants(const ConstantProtos&);
    double getDouble(const string&) const;

    ComponentMaker getMaker(const string&) const;
    void addMaker(const string&, ComponentMaker);

  private:
    std::unordered_map<string, double> doubleMap_;
    std::unordered_map<string, ComponentMaker> componentMakerMap_;
};

}  // namespace gui
}  // namespace rec
