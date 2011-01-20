#ifndef __REC_GUI_COLORS__
#define __REC_GUI_COLORS__

#include "rec/base/base.h"
#include "rec/gui/Color.pb.h"

namespace rec {
namespace gui {
namespace color {

Colour get(unsigned int i);
Colour get(const Colors& colors, unsigned int index);
void prepare(const Colors& colors, juce::Graphics* g);
const Colors& getDefaultColors();

Colour makeColour(const Color& color);
uint32 makeARGB(const Color& c);
uint32 nameToARGB(const string& name, const juce::Colour& dflt);

class ColorArg {
 public:
  ColorArg(uint32 c) : argb_(c) {}
  ColorArg(const Colour& c) : argb_(c.getARGB()) {}
  ColorArg(const Color& c) : argb_(makeARGB(c)) {}
  ColorArg(const string& s) : argb_(nameToARGB(s, juce::Colour())) {}

  operator Colour() const { return Colour(argb_); }
  operator uint32() const { return argb_; }
  operator Color() const {
    Color c;
    c.set_argb(argb_);
    return c;
  }

 private:
  uint32 argb_;
};

typedef const ColorArg& CCA;

Colors makeColors();
Colors makeColors(CCA);
Colors makeColors(CCA, CCA);
Colors makeColors(CCA, CCA, CCA);
Colors makeColors(CCA, CCA, CCA, CCA);
Colors makeColors(CCA, CCA, CCA, CCA, CCA);
Colors makeColors(CCA, CCA, CCA, CCA, CCA, CCA);
Colors makeColors(CCA, CCA, CCA, CCA, CCA, CCA, CCA);
Colors makeColors(CCA, CCA, CCA, CCA, CCA, CCA, CCA, CCA);

}  // namespace color
}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_COLORS__
