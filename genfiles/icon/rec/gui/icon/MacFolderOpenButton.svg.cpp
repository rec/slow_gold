#include "rec/gui/icon/MacFolderOpenButton.svg.h"
#include "rec/base/ArraySize.h"
#include "rec/util/Binary.h"

namespace rec {
namespace gui {
namespace icon {

using juce::Drawable;

// Created by the command line:
// new --namespace=rec.gui.icon --output=genfiles/icon/rec/gui/icon art/icon/MacFolderOpenButton.svg

Drawable* MacFolderOpenButton::create() {
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
  "<svg enable-background=\"new 0 0 17.256 20.557\" height=\"20.557\" i:pageBounds=\"0 25.9199 25.9199 0\" "
  "i:rulerOrigin=\"0 0\" i:viewOrigin=\"6.7178 22.9277\" overflow=\"visible\" viewBox=\"0 0 17.256 20.557\" "
  "width=\"17.256\" xml:space=\"preserve\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:a=\"http://ns.adobe.com/"
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
  "    <polygon i:knockout=\"Off\" points=\"0.657,20.557 0.657,1.106 17.256,10.783 \"/>\n"
  "    \n"
  "			\n"
  "    <polygon fill=\"#949494\" i:knockout=\"Off\" points=\"0,19.45 0,0 16.599,9.677 \"/>\n"
  "    \n"
  "		\n"
  "  </g>\n"
  "  \n"
  "	\n"
  "</svg>\n"
  " "
;
  return createBinary<Drawable>(data, arraysize(data), "MacFolderOpenButton.svg");
};

}  // namespace icon
}  // namespace gui
}  // namespace rec
