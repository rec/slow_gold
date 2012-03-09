#include "rec/gui/icon/ZoomInCursor.svg.h"
#include "rec/base/ArraySize.h"
#include "rec/util/Binary.h"

namespace rec {
namespace gui {
namespace icon {

using juce::Drawable;

// Created by the command line:
// new src/rec/gui/icon/ZoomInCursor.svg

Drawable* ZoomInCursor::create() {
  static const char data[] = "<?xml version=\"1.0\" ?>\n"
  "<!-- Generator: Adobe Illustrator 15.1.0, SVG Export Plug-In . SVG Version: 6.00 Build 0)  -->\n"
  "<!DOCTYPE svg\n"
  "  PUBLIC '-//W3C//DTD SVG 1.1//EN'\n"
  "  'http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd'>\n"
  "<svg enable-background=\"new 0 0 18.771 18.479\" height=\"18.479px\" id=\"Layer_1\" version=\"1.1\" viewBox=\"0 0 "
  "18.771 18.479\" width=\"18.771px\" x=\"0px\" xml:space=\"preserve\" xmlns=\"http://www.w3.org/2000/svg\" "
  "xmlns:xlink=\"http://www.w3.org/1999/xlink\" y=\"0px\">\n"
  "  \n"
  "\n"
  "  \n"
  "\n"
  "  <path d=\"M18.771,16.355l-3.899-3.899c0.815-1.262,1.296-2.761,1.296-4.373C16.166,3.626,12.54,0,8.083,0S0,3.626,0,"
  "8.083  s3.626,8.083,8.083,8.083c1.764,0,3.391-0.573,4.721-1.534l3.848,3.847L18.771,16.355z M2,8.083C2,4.729,4.729,2,"
  "8.083,2  c3.354,0,6.083,2.729,6.083,6.083c0,3.354-2.729,6.083-6.083,6.083C4.729,14.166,2,11.438,2,8.083z\"/>\n"
  "  \n"
  "\n"
  "</svg>\n"
  " "
;
  return createBinary<Drawable>(data, arraysize(data), "ZoomInCursor.svg");
};

}  // namespace icon
}  // namespace gui
}  // namespace rec
