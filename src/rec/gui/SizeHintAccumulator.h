#pragma once

#include "rec/gui/HasSizeHints.h"
#include "rec/gui/Orientation.h"
#include "rec/gui/SizeAccumulator.h"

namespace rec {
namespace gui {

class SizeHintAccumulator : public HasSizeHints {
  public:
    explicit SizeHintAccumulator(Orientation ori) : orientation_(ori) {}
    virtual ~SizeHintAccumulator() {}

    virtual Orientation getOrientation() const { return orientation_; }
    virtual int size(Hint h) const { return size_[h].size(); }

    void accumulate(double a) { accumulate(a, a, a); }
    void accumulate(double min, double max, double pref) {
        size_[HasSizeHints::MIN].accumulate(min);
        size_[HasSizeHints::MAX].accumulate(max);
        size_[HasSizeHints::PREF].accumulate(pref);
    }

    void clear() {
        size_[HasSizeHints::MIN].clear();
        size_[HasSizeHints::MAX].clear();
        size_[HasSizeHints::PREF].clear();
    }

  private:
    SizeAccumulator size_[HasSizeHints::LAST];
    const Orientation orientation_;

    DISALLOW_COPY_ASSIGN_AND_LEAKS(SizeHintAccumulator);
};

}  // namespace gui
}  // namespace rec

