#pragma once

namespace rec {
namespace data {

class Comparer {
  public:
    Comparer() {}

    virtual ~Comparer() {}
    virtual bool operator()(double x, double y) const { return x == y; }
    virtual bool operator()(float x, float y) const { return x == y; }

    template <typename T>
    bool operator()(T x, T y) const { return x == y; }
};

}  // namespace data
}  // namespace rec
