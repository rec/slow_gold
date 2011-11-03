#include "rec/gui/icon/PointingHand.svg.h"

#include "rec/base/ArraySize.h"
#include "rec/util/Binary.h"

namespace rec {
namespace gui {
namespace icon {

juce::Drawable* PointingHand::create() {
  static const char data[] = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
  "<svg\n"
  "   xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
  "   xmlns:cc=\"http://creativecommons.org/ns#\"\n"
  "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
  "   xmlns:svg=\"http://www.w3.org/2000/svg\"\n"
  "   xmlns=\"http://www.w3.org/2000/svg\"\n"
  "   xmlns:sodipodi=\"http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd\"\n"
  "   xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\"\n"
  "   width=\"340\"\n"
  "   height=\"440\"\n"
  "   id=\"Mano\"\n"
  "   version=\"1.0\">\n"
  "  <metadata id=\"Metadata\">\n"
  "    <rdf:RDF>\n"
  "      <cc:Work rdf:about=\"\">\n"
  "        <dc:format>image/svg+xml</dc:format>\n"
  "        <dc:type rdf:resource=\"http://purl.org/dc/dcmitype/StillImage\" />\n"
  "      </cc:Work>\n"
  "    </rdf:RDF>\n"
  "  </metadata>\n"
  "  <g\n"
  "     id=\"Mano\">\n"
  "    <path\n"
  "       style=\"fill:#000000;fill-opacity:1;fill-rule:evenodd;stroke:none\"\n"
  "       d=\"M 0,180 L 60,180 L 60,200 L 80,200 L 80,20 L 100,20 L 100,0 L 140,0 L 140,20 L 160,20 L 160,100 L 200,100 "
  "L 200,120 L 260,120 L 260,140 L 300,140 L 300,160 L 320,160 L 320,180 L 340,180 L 340,320 L 320,320 L 320,380 L 300,380 "
  "L 300,440 L 100,440 L 100,380 L 80,380 L 80,340 L 60,340 L 60,300 L 40,300 L 40,260 L 20,260 L 20,240 L 0,240 L 0,180 "
  "z\"\n"
  "       id=\"NigraBordero\" />\n"
  "    <path\n"
  "       style=\"fill:#ffffff;fill-opacity:1;fill-rule:evenodd;stroke:none\"\n"
  "       d=\"M 20,200 L 60,200 L 60,220 L 80,220 C 80,220 80,280 80,280 L 100,280 L 100,20 L 140,20 L 140,200 L 160,"
  "200 L 160,120 L 200,120 L 200,200 L 220,200 L 220,140 L 260,140 L 260,220 L 280,220 L 280,160 L 300,160 L 300,180 L 320,"
  "180 L 320,320 L 300,320 L 300,380 L 280,380 L 280,420 L 120,420 L 120,380 L 100,380 L 100,340 L 80,340 L 80,300 L 60,"
  "300 L 60,260 L 40,260 L 40,240 L 20,240 L 20,200 z\"\n"
  "       id=\"BlankaIntero\" />\n"
  "  </g>\n"
  "</svg>\n"
  "\n"
;
  return createBinary<juce::Drawable>(data, arraysize(data));
};

}  // namespace icon
}  // namespace gui
}  // namespace rec
