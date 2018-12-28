#include "rec/gui/Color.h"
#include "rec/base/ArraySize.h"

using namespace juce;

namespace rec {
namespace gui {
namespace color {

namespace {

std::pair<Colour*, Colour*> getColours() {
    static Colour COLORS[] = {
        Colours::white,
        Colours::lightblue,
        Colours::seagreen,
        juce::Colour(0xffd3d3d3),
        juce::Colour(0xff809090),
        juce::Colours::red,
        juce::Colours::black,
        juce::Colour(0xff607070),
        // Colours::grey,
        // Colours::blue, //grey
    };
    return std::make_pair(COLORS, COLORS + arraysize(COLORS));
}

#ifdef UNUSED_CODE
Colors getDefaultInternal() {
    Colors colors;
    std::pair<Colour*, Colour*> colours = getColours();
    for (Colour* c = colours.first; c != colours.second; ++c)
        colors.add_color()->set_argb(c->getARGB());
    return colors;
};

const Colors& getDefaultColors() {
    static Colors colors = getDefaultInternal();
    return colors;
}
#endif

ColourMap emptyMap_;

}  // namespace

Colour get(int i) {
    std::pair<Colour*, Colour*> colours = getColours();
    if (i < colours.second - colours.first)
        return colours.first[i];

    LOG(DFATAL) << "Couldn't get color " << i;
    return colours.second[-1];
};

Colour get(const Colors& colors, int i) {
    return i < colors.color_size() ?
            makeColour(colors.color(i), emptyMap_) : get(i);
}

Colour makeColour(const Color& c, const ColourMap& map) {
    if (c.has_name()) {
        try {
            return map.at(c.name());
        } catch (std::out_of_range&) {
        }

        String name(c.name());
        Colour cl = Colours::findColourForName(c.name(), Colours::black);
        if (cl != Colours::black or
                Colours::findColourForName(c.name(), Colours::white) == cl) {
            return cl;
        }
        LOG(DFATAL) << "Couldn't understand colour name " << c.name();
    }

    if (c.has_argb())
        return Colour(c.argb());

    if (c.has_rgb())
        return Colour((c.alpha() << 24) | c.rgb());

    return Colour(static_cast<uint8>(c.red()),
                                static_cast<uint8>(c.green()),
                                static_cast<uint8>(c.blue()),
                                static_cast<uint8>(c.alpha()));
}

}  // namespace color
}  // namespace gui
}  // namespace rec
