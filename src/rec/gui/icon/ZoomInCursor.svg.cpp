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
  "<!-- Generator: Adobe Illustrator 11 Build 196, SVG Export Plug-In . SVG Version: 6.0.0 Build 78)  -->\n"
  "<!DOCTYPE svg\n"
  "  PUBLIC '-//W3C//DTD SVG 1.0//EN'\n"
  "  'http://www.w3.org/TR/2001/REC-SVG-20010904/DTD/svg10.dtd' [\n"
  "	<!ENTITY ns_flows \"http://ns.adobe.com/Flows/1.0/\">\n"
  "	<!ENTITY ns_extend \"http://ns.adobe.com/Extensibility/1.0/\">\n"
  "	<!ENTITY ns_ai \"http://ns.adobe.com/AdobeIllustrator/10.0/\">\n"
  "	<!ENTITY ns_graphs \"http://ns.adobe.com/Graphs/1.0/\">\n"
  "	<!ENTITY ns_vars \"http://ns.adobe.com/Variables/1.0/\">\n"
  "	<!ENTITY ns_imrep \"http://ns.adobe.com/ImageReplacement/1.0/\">\n"
  "	<!ENTITY ns_sfw \"http://ns.adobe.com/SaveForWeb/1.0/\">\n"
  "	<!ENTITY ns_custom \"http://ns.adobe.com/GenericCustomNamespace/1.0/\">\n"
  "	<!ENTITY ns_adobe_xpath \"http://ns.adobe.com/XPath/1.0/\">\n"
  "	<!ENTITY ns_svg \"http://www.w3.org/2000/svg\">\n"
  "	<!ENTITY ns_xlink \"http://www.w3.org/1999/xlink\">\n"
  "]>\n"
  "<svg enable-background=\"new 0 0 18.77 18.478\" height=\"18.478\" i:pageBounds=\"0 25.9199 25.9199 0\" "
  "i:rulerOrigin=\"0 0\" i:viewOrigin=\"4.208 22.0869\" overflow=\"visible\" viewBox=\"0 0 18.77 18.478\" width=\"18.77\" "
  "xml:space=\"preserve\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:a=\"http://ns.adobe.com/AdobeSVGViewerExtensions/3.0/"
  "\" xmlns:graph=\"http://ns.adobe.com/Graphs/1.0/\" xmlns:i=\"http://ns.adobe.com/AdobeIllustrator/10.0/\" "
  "xmlns:x=\"http://ns.adobe.com/Extensibility/1.0/\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n"
  "  \n"
  "	\n"
  "  \n"
  "		\n"
  "  <g i:dimmedPercent=\"50\" i:layer=\"yes\" i:rgbTrio=\"#4F008000FFFF\" id=\"Layer_1\">\n"
  "    \n"
  "			\n"
  "				\n"
  "    <circle cx=\"8.083\" cy=\"8.083\" fill=\"#F2F2F2\" i:knockout=\"Off\" r=\"7.083\" stroke=\"#000000\" "
  "stroke-linecap=\"round\" stroke-linejoin=\"round\" stroke-width=\"2\"/>\n"
  "     \n"
  "			\n"
  "				\n"
  "    <rect height=\"3\" i:knockout=\"Off\" transform=\"matrix(0.7072 0.707 -0.707 0.7072 15.276 -6.4995)\" "
  "width=\"6.29\" x=\"12.34\" y=\"13.693\"/>\n"
  "     \n"
  "		\n"
  "  </g>\n"
  "  \n"
  "	\n"
  "</svg>\n"
  " "
;
  return createBinary<Drawable>(data, arraysize(data), "ZoomInCursor.svg");
};

}  // namespace icon
}  // namespace gui
}  // namespace rec