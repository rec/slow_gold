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
  "<svg enable-background=\"new 0 0 18.771 18.478\" height=\"18.478\" i:pageBounds=\"0 25.9199 25.9199 0\" "
  "i:rulerOrigin=\"0 0\" i:viewOrigin=\"4.208 22.0869\" overflow=\"visible\" viewBox=\"0 0 18.771 18.478\" "
  "width=\"18.771\" xml:space=\"preserve\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:a=\"http://ns.adobe.com/"
  "AdobeSVGViewerExtensions/3.0/\" xmlns:graph=\"http://ns.adobe.com/Graphs/1.0/\" xmlns:i=\"http://ns.adobe.com/"
  "AdobeIllustrator/10.0/\" xmlns:x=\"http://ns.adobe.com/Extensibility/1.0/\" xmlns:xlink=\"http://www.w3.org/1999/"
  "xlink\">\n"
  "  \n"
  "	\n"
  "  \n"
  "		\n"
  "  <g i:dimmedPercent=\"50\" i:layer=\"yes\" i:rgbTrio=\"#4F008000FFFF\" id=\"Layer_1\">\n"
  "    \n"
  "			\n"
  "    <path d=\"M18.771,16.355l-3.9-3.899c0.816-1.262,1.296-2.761,1.296-4.373C16.166,3.626,12.54,0,8.083,0S0,3.626,0,"
  "8.083     s3.626,8.083,8.083,8.083c1.763,0,3.39-0.573,4.72-1.534l3.847,3.846L18.771,16.355z M2,8.083C2,4.729,4.729,2,"
  "8.083,2     c3.354,0,6.083,2.729,6.083,6.083c0,3.354-2.729,6.083-6.083,6.083C4.729,14.166,2,11.438,2,8.083z\"/>\n"
  "    \n"
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
