#include "rec/gui/icon/AudioCard.svg.h"

#include "rec/base/ArraySize.h"
#include "rec/data/Binary.h"

namespace rec {
namespace gui {
namespace icon {

juce::Drawable* AudioCard::create() {
  static const char data[] = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n"
  "<!-- Created with Inkscape (http://www.inkscape.org/) -->\n"
  "<svg\n"
  "   xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
  "   xmlns:cc=\"http://creativecommons.org/ns#\"\n"
  "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
  "   xmlns:svg=\"http://www.w3.org/2000/svg\"\n"
  "   xmlns=\"http://www.w3.org/2000/svg\"\n"
  "   xmlns:xlink=\"http://www.w3.org/1999/xlink\"\n"
  "   xmlns:sodipodi=\"http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd\"\n"
  "   xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\"\n"
  "   width=\"48px\"\n"
  "   height=\"48px\"\n"
  "   id=\"svg19135\"\n"
  "   sodipodi:version=\"0.32\"\n"
  "   inkscape:version=\"0.46\"\n"
  "   sodipodi:docbase=\"/home/tigert/cvs/freedesktop.org/tango-icon-theme/"
  "scalable/devices\"\n"
  "   sodipodi:docname=\"audio-card.svg\"\n"
  "   inkscape:output_extension=\"org.inkscape.output.svg.inkscape\">\n"
  "  <defs\n"
  "     id=\"defs3\">\n"
  "    <inkscape:perspective\n"
  "       sodipodi:type=\"inkscape:persp3d\"\n"
  "       inkscape:vp_x=\"0 : 24 : 1\"\n"
  "       inkscape:vp_y=\"0 : 1000 : 0\"\n"
  "       inkscape:vp_z=\"48 : 24 : 1\"\n"
  "       inkscape:persp3d-origin=\"24 : 16 : 1\"\n"
  "       id=\"perspective53\" />\n"
  "    <linearGradient\n"
  "       id=\"linearGradient2497\">\n"
  "      <stop\n"
  "         style=\"stop-color:#ffffff;stop-opacity:0.60824740;\"\n"
  "         offset=\"0.0000000\"\n"
  "         id=\"stop2499\" />\n"
  "      <stop\n"
  "         style=\"stop-color:#ffffff;stop-opacity:0;\"\n"
  "         offset=\"1\"\n"
  "         id=\"stop2501\" />\n"
  "    </linearGradient>\n"
  "    <linearGradient\n"
  "       id=\"linearGradient19474\">\n"
  "      <stop\n"
  "         style=\"stop-color:#ffffff;stop-opacity:1.0000000;\"\n"
  "         offset=\"0.0000000\"\n"
  "         id=\"stop19476\" />\n"
  "      <stop\n"
  "         style=\"stop-color:#939393;stop-opacity:1.0000000;\"\n"
  "         offset=\"1.0000000\"\n"
  "         id=\"stop19478\" />\n"
  "    </linearGradient>\n"
  "    <linearGradient\n"
  "       inkscape:collect=\"always\"\n"
  "       id=\"linearGradient19278\">\n"
  "      <stop\n"
  "         style=\"stop-color:#000000;stop-opacity:1;\"\n"
  "         offset=\"0\"\n"
  "         id=\"stop19280\" />\n"
  "      <stop\n"
  "         style=\"stop-color:#000000;stop-opacity:0;\"\n"
  "         offset=\"1\"\n"
  "         id=\"stop19282\" />\n"
  "    </linearGradient>\n"
  "    <linearGradient\n"
  "       id=\"linearGradient19270\">\n"
  "      <stop\n"
  "         id=\"stop19272\"\n"
  "         offset=\"0.0000000\"\n"
  "         style=\"stop-color:#aaaaaa;stop-opacity:1.0000000;\" />\n"
  "      <stop\n"
  "         id=\"stop19274\"\n"
  "         offset=\"1.0000000\"\n"
  "         style=\"stop-color:#505050;stop-opacity:1.0000000;\" />\n"
  "    </linearGradient>\n"
  "    <linearGradient\n"
  "       id=\"linearGradient19149\">\n"
  "      <stop\n"
  "         style=\"stop-color:#adadad;stop-opacity:1.0000000;\"\n"
  "         offset=\"0.0000000\"\n"
  "         id=\"stop19151\" />\n"
  "      <stop\n"
  "         style=\"stop-color:#747474;stop-opacity:1.0000000;\"\n"
  "         offset=\"1.0000000\"\n"
  "         id=\"stop19153\" />\n"
  "    </linearGradient>\n"
  "    <radialGradient\n"
  "       inkscape:collect=\"always\"\n"
  "       xlink:href=\"#linearGradient19149\"\n"
  "       id=\"radialGradient19155\"\n"
  "       gradientTransform=\"scale(1.347925,0.741881)\"\n"
  "       cx=\"16.331211\"\n"
  "       cy=\"34.833511\"\n"
  "       fx=\"16.331211\"\n"
  "       fy=\"34.833511\"\n"
  "       r=\"15.231354\"\n"
  "       gradientUnits=\"userSpaceOnUse\" />\n"
  "    <radialGradient\n"
  "       inkscape:collect=\"always\"\n"
  "       xlink:href=\"#linearGradient19149\"\n"
  "       id=\"radialGradient19161\"\n"
  "       gradientUnits=\"userSpaceOnUse\"\n"
  "       gradientTransform=\"scale(1.347925,0.741881)\"\n"
  "       cx=\"25.940556\"\n"
  "       cy=\"41.706387\"\n"
  "       fx=\"25.940556\"\n"
  "       fy=\"41.706387\"\n"
  "       r=\"26.594908\" />\n"
  "    <linearGradient\n"
  "       inkscape:collect=\"always\"\n"
  "       xlink:href=\"#linearGradient19270\"\n"
  "       id=\"linearGradient19175\"\n"
  "       gradientTransform=\"matrix(1.700880,0.000000,0.000000,0.587931,"
  "-1.374996,-7.214286)\"\n"
  "       x1=\"6.8835502\"\n"
  "       y1=\"56.288612\"\n"
  "       x2=\"16.294504\"\n"
  "       y2=\"68.766663\"\n"
  "       gradientUnits=\"userSpaceOnUse\" />\n"
  "    <linearGradient\n"
  "       inkscape:collect=\"always\"\n"
  "       xlink:href=\"#linearGradient19149\"\n"
  "       id=\"linearGradient19243\"\n"
  "       gradientUnits=\"userSpaceOnUse\"\n"
  "       gradientTransform=\"matrix(1.411264,0.000000,0.000000,0.708585,"
  "-1.517853,-6.857043)\"\n"
  "       x1=\"5.1625452\"\n"
  "       y1=\"50.805511\"\n"
  "       x2=\"26.171595\"\n"
  "       y2=\"50.805479\" />\n"
  "    <radialGradient\n"
  "       inkscape:collect=\"always\"\n"
  "       xlink:href=\"#linearGradient19278\"\n"
  "       id=\"radialGradient19284\"\n"
  "       gradientTransform=\"scale(1.357519,0.736638)\"\n"
  "       cx=\"17.579761\"\n"
  "       cy=\"47.402553\"\n"
  "       fx=\"17.579761\"\n"
  "       fy=\"47.402553\"\n"
  "       r=\"16.798437\"\n"
  "       gradientUnits=\"userSpaceOnUse\" />\n"
  "    <radialGradient\n"
  "       inkscape:collect=\"always\"\n"
  "       xlink:href=\"#linearGradient19474\"\n"
  "       id=\"radialGradient19480\"\n"
  "       gradientTransform=\"scale(1.287593,0.776643)\"\n"
  "       cx=\"30.873167\"\n"
  "       cy=\"31.265368\"\n"
  "       fx=\"30.873167\"\n"
  "       fy=\"31.265368\"\n"
  "       r=\"3.2488604\"\n"
  "       gradientUnits=\"userSpaceOnUse\" />\n"
  "    <radialGradient\n"
  "       inkscape:collect=\"always\"\n"
  "       xlink:href=\"#linearGradient19474\"\n"
  "       id=\"radialGradient19488\"\n"
  "       gradientUnits=\"userSpaceOnUse\"\n"
  "       gradientTransform=\"scale(1.287593,0.776643)\"\n"
  "       cx=\"30.873167\"\n"
  "       cy=\"31.265368\"\n"
  "       fx=\"30.873167\"\n"
  "       fy=\"31.265368\"\n"
  "       r=\"3.2488604\" />\n"
  "    <radialGradient\n"
  "       inkscape:collect=\"always\"\n"
  "       xlink:href=\"#linearGradient19474\"\n"
  "       id=\"radialGradient19494\"\n"
  "       gradientUnits=\"userSpaceOnUse\"\n"
  "       gradientTransform=\"scale(1.287593,0.776643)\"\n"
  "       cx=\"30.873167\"\n"
  "       cy=\"31.265368\"\n"
  "       fx=\"30.873167\"\n"
  "       fy=\"31.265368\"\n"
  "       r=\"3.2488604\" />\n"
  "    <radialGradient\n"
  "       inkscape:collect=\"always\"\n"
  "       xlink:href=\"#linearGradient19474\"\n"
  "       id=\"radialGradient19496\"\n"
  "       gradientUnits=\"userSpaceOnUse\"\n"
  "       gradientTransform=\"scale(1.287593,0.776643)\"\n"
  "       cx=\"30.873167\"\n"
  "       cy=\"31.265368\"\n"
  "       fx=\"30.873167\"\n"
  "       fy=\"31.265368\"\n"
  "       r=\"3.2488604\" />\n"
  "    <linearGradient\n"
  "       inkscape:collect=\"always\"\n"
  "       xlink:href=\"#linearGradient19149\"\n"
  "       id=\"linearGradient2479\"\n"
  "       gradientUnits=\"userSpaceOnUse\"\n"
  "       gradientTransform=\"matrix(1.411264,0.000000,0.000000,0.708585,"
  "-1.517853,-5.016059)\"\n"
  "       x1=\"5.1625452\"\n"
  "       y1=\"50.805511\"\n"
  "       x2=\"26.171595\"\n"
  "       y2=\"50.805479\" />\n"
  "    <linearGradient\n"
  "       inkscape:collect=\"always\"\n"
  "       xlink:href=\"#linearGradient2497\"\n"
  "       id=\"linearGradient2503\"\n"
  "       gradientTransform=\"matrix(1.072527,0.000000,0.000000,0.932378,"
  "0.500000,0.750000)\"\n"
  "       x1=\"11.562314\"\n"
  "       y1=\"8.0809259\"\n"
  "       x2=\"30.750120\"\n"
  "       y2=\"53.658985\"\n"
  "       gradientUnits=\"userSpaceOnUse\" />\n"
  "  </defs>\n"
  "  <sodipodi:namedview\n"
  "     id=\"base\"\n"
  "     pagecolor=\"#ffffff\"\n"
  "     bordercolor=\"#666666\"\n"
  "     borderopacity=\"0.20392157\"\n"
  "     inkscape:pageopacity=\"0.0\"\n"
  "     inkscape:pageshadow=\"2\"\n"
  "     inkscape:zoom=\"4\"\n"
  "     inkscape:cx=\"24.206131\"\n"
  "     inkscape:cy=\"11.812843\"\n"
  "     inkscape:current-layer=\"layer1\"\n"
  "     showgrid=\"false\"\n"
  "     inkscape:grid-bbox=\"true\"\n"
  "     inkscape:document-units=\"px\"\n"
  "     inkscape:window-width=\"831\"\n"
  "     inkscape:window-height=\"806\"\n"
  "     inkscape:window-x=\"310\"\n"
  "     inkscape:window-y=\"42\"\n"
  "     inkscape:showpageshadow=\"false\" />\n"
  "  <metadata\n"
  "     id=\"metadata4\">\n"
  "    <rdf:RDF>\n"
  "      <cc:Work\n"
  "         rdf:about=\"\">\n"
  "        <dc:format>image/svg+xml</dc:format>\n"
  "        <dc:type\n"
  "           rdf:resource=\"http://purl.org/dc/dcmitype/StillImage\" />\n"
  "        <dc:title>Audio Card</dc:title>\n"
  "        <dc:description>Audio Card Device</dc:description>\n"
  "        <dc:source>http://jimmac.musichall.cz</dc:source>\n"
  "        <dc:creator>\n"
  "          <cc:Agent>\n"
  "            <dc:title>Jakub Steiner</dc:title>\n"
  "          </cc:Agent>\n"
  "        </dc:creator>\n"
  "        <cc:license\n"
  "           rdf:resource=\"http://creativecommons.org/licenses/publicdomain/"
  "\" />\n"
  "        <dc:subject>\n"
  "          <rdf:Bag>\n"
  "            <rdf:li>sound</rdf:li>\n"
  "            <rdf:li>audio</rdf:li>\n"
  "            <rdf:li>card</rdf:li>\n"
  "            <rdf:li>device</rdf:li>\n"
  "          </rdf:Bag>\n"
  "        </dc:subject>\n"
  "      </cc:Work>\n"
  "      <cc:License\n"
  "         rdf:about=\"http://creativecommons.org/licenses/publicdomain/"
  "\">\n"
  "        <cc:permits\n"
  "           rdf:resource=\"http://creativecommons.org/ns#Reproduction\" /"
  ">\n"
  "        <cc:permits\n"
  "           rdf:resource=\"http://creativecommons.org/ns#Distribution\" /"
  ">\n"
  "        <cc:permits\n"
  "           rdf:resource=\"http://creativecommons.org/ns#DerivativeWorks\" /"
  ">\n"
  "      </cc:License>\n"
  "    </rdf:RDF>\n"
  "  </metadata>\n"
  "  <g\n"
  "     id=\"layer1\"\n"
  "     inkscape:label=\"Layer 1\"\n"
  "     inkscape:groupmode=\"layer\">\n"
  "    <path\n"
  "       sodipodi:nodetypes=\"cccccccscccccccccsccccccc\"\n"
  "       style=\"color:#000000;fill:url(#linearGradient2479);"
  "fill-opacity:1.0000000;fill-rule:evenodd;stroke:#4c4c4c;"
  "stroke-width:2.0000000;stroke-linecap:butt;stroke-linejoin:miter;marker:none;"
  "marker-start:none;marker-mid:none;marker-end:none;stroke-miterlimit:4.0000000;"
  "stroke-dashoffset:0.0000000;stroke-opacity:1.0000000;visibility:visible;"
  "display:inline;overflow:visible\"\n"
  "       d=\"M 24.062500,5.5839466 C 19.883145,5.5839466 15.987925,6.3923840 "
  "12.750000,7.7401966 C 12.091421,7.4306631 11.400590,7.1151967 10.531250,"
  "7.1151966 C 8.3067593,7.1151966 6.4999999,8.3024437 6.5000000,9.7714466 C "
  "6.5000000,10.288319 6.7696230,10.769230 7.1562500,11.177697 C 4.9340629,"
  "13.221121 3.6250000,16.032281 3.6250000,18.687500 C 3.6250000,20.698501 "
  "4.4230122,22.411723 5.7500000,24.104473 C 4.4498570,24.654421 3.5625000,"
  "25.572389 3.5625000,27.108915 C 3.5625000,28.816578 5.6328602,30.202666 "
  "8.2187500,30.202665 C 8.5918621,30.202665 8.9332645,30.100925 9.2812500,"
  "30.046415 C 9.1705316,30.417047 9.0625000,30.785350 9.0625000,31.171415 C "
  "9.0624997,31.867205 9.0625000,32.707859 9.0625000,33.403648 C 9.0624997,"
  "37.615415 15.892816,41.028647 24.281250,41.028648 C 32.669685,41.028649 "
  "39.468750,37.615414 39.468750,33.403648 C 39.468750,32.706166 39.468750,"
  "31.868898 39.468750,31.171415 C 39.468750,30.763093 39.373061,30.374844 "
  "39.250000,29.983915 C 39.778288,30.120373 40.336288,30.202665 40.937500,"
  "30.202665 C 43.523389,30.202665 45.713388,28.816578 45.713388,27.108915 C "
  "45.713388,25.260726 44.352914,24.237474 42.593750,23.791973 C 43.775099,"
  "22.177335 44.468750,20.577983 44.468750,18.687500 C 44.468750,16.249390 "
  "43.337049,13.647412 41.437500,11.708947 C 42.196991,11.224865 42.687500,"
  "10.523021 42.687500,9.7714466 C 42.687500,8.3024433 40.880739,7.1151968 "
  "38.656250,7.1151966 C 37.523789,7.1151966 36.513565,7.4304996 35.781250,"
  "7.9276966 C 32.456778,6.4629896 28.436227,5.5839465 24.062500,5.5839466 z "
  "\"\n"
  "       id=\"path19447\" />\n"
  "    <path\n"
  "       sodipodi:type=\"arc\"\n"
  "       style=\"color:#000000;fill:url(#radialGradient19284);"
  "fill-opacity:1.0000000;fill-rule:evenodd;stroke:none;stroke-width:4.0000000;"
  "stroke-linecap:butt;stroke-linejoin:miter;marker:none;marker-start:none;"
  "marker-mid:none;marker-end:none;stroke-miterlimit:4.0000000;"
  "stroke-dashoffset:0.0000000;stroke-opacity:1.0000000;visibility:visible;"
  "display:inline;overflow:visible\"\n"
  "       id=\"path19276\"\n"
  "       sodipodi:cx=\"23.864855\"\n"
  "       sodipodi:cy=\"34.918526\"\n"
  "       sodipodi:rx=\"22.804193\"\n"
  "       sodipodi:ry=\"12.374369\"\n"
  "       d=\"M 46.669048 34.918526 A 22.804193 12.374369 0 1 1  1.0606613,"
  "34.918526 A 22.804193 12.374369 0 1 1  46.669048 34.918526 z\"\n"
  "       transform=\"translate(0.332106,-0.646447)\" />\n"
  "    <path\n"
  "       style=\"color:#000000;fill:url(#linearGradient19243);"
  "fill-opacity:1.0000000;fill-rule:evenodd;stroke:none;stroke-width:2.0000000;"
  "stroke-linecap:butt;stroke-linejoin:miter;marker:none;marker-start:none;"
  "marker-mid:none;marker-end:none;stroke-miterlimit:4.0000000;"
  "stroke-dashoffset:0.0000000;stroke-opacity:1.0000000;visibility:visible;"
  "display:inline;overflow:visible\"\n"
  "       d=\"M 24.294647,21.455457 C 15.906213,21.455457 9.0758969,24.868690 "
  "9.0758969,29.080457 C 9.0758969,29.776246 9.0758969,32.384668 9.0758969,"
  "33.080457 C 9.0758969,37.292223 15.906213,40.705456 24.294647,40.705457 C "
  "32.683082,40.705457 39.482147,37.292223 39.482147,33.080457 C 39.482147,"
  "32.382974 39.482147,29.777940 39.482147,29.080457 C 39.482147,24.868691 "
  "32.683082,21.455457 24.294647,21.455457 z \"\n"
  "       id=\"path19181\"\n"
  "       sodipodi:nodetypes=\"ccccccc\" />\n"
  "    <path\n"
  "       transform=\"translate(-0.483935,-6.734736)\"\n"
  "       d=\"M 39.142858 35.142857 A 14.285714 6.0000000 0 1 1  10.571429,"
  "35.142857 A 14.285714 6.0000000 0 1 1  39.142858 35.142857 z\"\n"
  "       sodipodi:ry=\"6.0000000\"\n"
  "       sodipodi:rx=\"14.285714\"\n"
  "       sodipodi:cy=\"35.142857\"\n"
  "       sodipodi:cx=\"24.857143\"\n"
  "       id=\"path19268\"\n"
  "       style=\"color:#000000;fill:#ffffff;fill-opacity:0.59649122;"
  "fill-rule:evenodd;stroke:none;stroke-width:4.0000000;stroke-linecap:butt;"
  "stroke-linejoin:miter;marker:none;marker-start:none;marker-mid:none;"
  "marker-end:none;stroke-miterlimit:4.0000000;stroke-dashoffset:0.0000000;"
  "stroke-opacity:1.0000000;visibility:visible;display:inline;"
  "overflow:visible\"\n"
  "       sodipodi:type=\"arc\" />\n"
  "    <path\n"
  "       sodipodi:type=\"arc\"\n"
  "       style=\"color:#000000;fill:#afafaf;fill-opacity:1.0000000;"
  "fill-rule:evenodd;stroke:none;stroke-width:4.0000000;stroke-linecap:butt;"
  "stroke-linejoin:miter;marker:none;marker-start:none;marker-mid:none;"
  "marker-end:none;stroke-miterlimit:4.0000000;stroke-dashoffset:0.0000000;"
  "stroke-opacity:1.0000000;visibility:visible;display:inline;"
  "overflow:visible\"\n"
  "       id=\"path19218\"\n"
  "       sodipodi:cx=\"24.857143\"\n"
  "       sodipodi:cy=\"35.142857\"\n"
  "       sodipodi:rx=\"14.285714\"\n"
  "       sodipodi:ry=\"6.0000000\"\n"
  "       d=\"M 39.142858 35.142857 A 14.285714 6.0000000 0 1 1  10.571429,"
  "35.142857 A 14.285714 6.0000000 0 1 1  39.142858 35.142857 z\"\n"
  "       transform=\"translate(-0.660711,-6.999900)\" />\n"
  "    <path\n"
  "       style=\"color:#000000;fill:url(#linearGradient19175);"
  "fill-opacity:1.0000000;fill-rule:evenodd;stroke:none;stroke-width:2.0000000;"
  "stroke-linecap:butt;stroke-linejoin:miter;marker:none;marker-start:none;"
  "marker-mid:none;marker-end:none;stroke-miterlimit:4.0000000;"
  "stroke-dashoffset:0.0000000;stroke-opacity:1.0000000;visibility:visible;"
  "display:inline;overflow:visible\"\n"
  "       d=\"M 43.482147,20.500000 L 37.767861,30.071428 C 31.910718,"
  "34.785714 18.339290,35.071429 10.910718,30.214286 L 5.1964325,21.357143 L "
  "43.482147,20.500000 z \"\n"
  "       id=\"path19173\"\n"
  "       sodipodi:nodetypes=\"ccccc\" />\n"
  "    <path\n"
  "       style=\"color:#000000;fill:#737373;fill-opacity:1.0000000;"
  "fill-rule:evenodd;stroke:none;stroke-width:2.2343740;stroke-linecap:butt;"
  "stroke-linejoin:miter;marker:none;marker-start:none;marker-mid:none;"
  "marker-end:none;stroke-miterlimit:4.0000000;stroke-dashoffset:0.0000000;"
  "stroke-opacity:1.0000000;visibility:visible;display:inline;"
  "overflow:visible\"\n"
  "       d=\"M 24.062500,6.3062181 C 12.785933,6.3062181 3.6250001,12.008361 "
  "3.6250000,19.056216 C 3.6250000,21.067217 4.4230122,22.957216 5.7500000,"
  "24.649966 C 4.4498570,25.199914 3.5625000,26.117882 3.5625000,27.212466 C "
  "3.5625000,28.920129 5.6328602,30.306217 8.2187500,30.306216 C 9.6529730,"
  "30.306216 10.890466,29.852324 11.750000,29.181216 C 15.181878,30.813628 "
  "19.420156,31.837466 24.062500,31.837466 C 29.019138,31.837466 33.492369,"
  "30.674743 37.031250,28.837466 C 37.860077,29.709230 39.264814,30.306216 "
  "40.937500,30.306216 C 43.523389,30.306216 45.625000,28.920129 45.625000,"
  "27.212466 C 45.625000,25.894607 44.352914,24.782967 42.593750,24.337466 C "
  "43.775099,22.722828 44.468750,20.946699 44.468750,19.056216 C 44.468750,"
  "12.008362 35.339066,6.3062179 24.062500,6.3062181 z \"\n"
  "       id=\"path19500\" />\n"
  "    <path\n"
  "       transform=\"translate(-34.81183,-2.226137)\"\n"
  "       d=\"M 47.729706 28.819729 A 4.6845822 3.0935922 0 1 1  38.360542,"
  "28.819729 A 4.6845822 3.0935922 0 1 1  47.729706 28.819729 z\"\n"
  "       sodipodi:ry=\"3.0935922\"\n"
  "       sodipodi:rx=\"4.6845822\"\n"
  "       sodipodi:cy=\"28.819729\"\n"
  "       sodipodi:cx=\"43.045124\"\n"
  "       id=\"path19441\"\n"
  "       style=\"color:#000000;fill:#cbcbcb;fill-opacity:1.0000000;"
  "fill-rule:evenodd;stroke:none;stroke-width:2.2343740;stroke-linecap:butt;"
  "stroke-linejoin:miter;marker:none;marker-start:none;marker-mid:none;"
  "marker-end:none;stroke-miterlimit:4.0000000;stroke-dashoffset:0.0000000;"
  "stroke-opacity:1.0000000;visibility:visible;display:inline;"
  "overflow:visible\"\n"
  "       sodipodi:type=\"arc\" />\n"
  "    <path\n"
  "       sodipodi:type=\"arc\"\n"
  "       style=\"color:#000000;fill:#cbcbcb;fill-opacity:1.0000000;"
  "fill-rule:evenodd;stroke:none;stroke-width:2.2343740;stroke-linecap:butt;"
  "stroke-linejoin:miter;marker:none;marker-start:none;marker-mid:none;"
  "marker-end:none;stroke-miterlimit:4.0000000;stroke-dashoffset:0.0000000;"
  "stroke-opacity:1.0000000;visibility:visible;display:inline;"
  "overflow:visible\"\n"
  "       id=\"path19443\"\n"
  "       sodipodi:cx=\"43.045124\"\n"
  "       sodipodi:cy=\"28.819729\"\n"
  "       sodipodi:rx=\"4.6845822\"\n"
  "       sodipodi:ry=\"3.0935922\"\n"
  "       d=\"M 47.729706 28.819729 A 4.6845822 3.0935922 0 1 1  38.360542,"
  "28.819729 A 4.6845822 3.0935922 0 1 1  47.729706 28.819729 z\"\n"
  "       transform=\"matrix(0.860242,0.000000,0.000000,0.860242,-26.51038,"
  "-14.90547)\" />\n"
  "    <path\n"
  "       d=\"M 43.857143 23.714285 A 18.285715 11.428572 0 1 1  7.2857132,"
  "23.714285 A 18.285715 11.428572 0 1 1  43.857143 23.714285 z\"\n"
  "       sodipodi:ry=\"11.428572\"\n"
  "       sodipodi:rx=\"18.285715\"\n"
  "       sodipodi:cy=\"23.714285\"\n"
  "       sodipodi:cx=\"25.571428\"\n"
  "       id=\"path19163\"\n"
  "       style=\"color:#000000;fill:#cbcbcb;fill-opacity:1.0000000;"
  "fill-rule:evenodd;stroke:none;stroke-width:2.0000000;stroke-linecap:butt;"
  "stroke-linejoin:miter;marker:none;marker-start:none;marker-mid:none;"
  "marker-end:none;stroke-miterlimit:4.0000000;stroke-dashoffset:0.0000000;"
  "stroke-opacity:1.0000000;visibility:visible;display:inline;"
  "overflow:visible\"\n"
  "       sodipodi:type=\"arc\"\n"
  "       transform=\"matrix(1.117187,0.000000,0.000000,1.117187,-4.514504,"
  "-8.045078)\" />\n"
  "    <path\n"
  "       sodipodi:type=\"arc\"\n"
  "       style=\"color:#000000;fill:#cbcbcb;fill-opacity:1.0000000;"
  "fill-rule:evenodd;stroke:none;stroke-width:2.2343740;stroke-linecap:butt;"
  "stroke-linejoin:miter;marker:none;marker-start:none;marker-mid:none;"
  "marker-end:none;stroke-miterlimit:4.0000000;stroke-dashoffset:0.0000000;"
  "stroke-opacity:1.0000000;visibility:visible;display:inline;"
  "overflow:visible\"\n"
  "       id=\"path19439\"\n"
  "       sodipodi:cx=\"43.045124\"\n"
  "       sodipodi:cy=\"28.819729\"\n"
  "       sodipodi:rx=\"4.6845822\"\n"
  "       sodipodi:ry=\"3.0935922\"\n"
  "       d=\"M 47.729706 28.819729 A 4.6845822 3.0935922 0 1 1  38.360542,"
  "28.819729 A 4.6845822 3.0935922 0 1 1  47.729706 28.819729 z\"\n"
  "       transform=\"translate(-2.104706,-2.226137)\" />\n"
  "    <path\n"
  "       transform=\"matrix(0.860242,0.000000,0.000000,0.860242,1.625659,"
  "-14.90547)\"\n"
  "       d=\"M 47.729706 28.819729 A 4.6845822 3.0935922 0 1 1  38.360542,"
  "28.819729 A 4.6845822 3.0935922 0 1 1  47.729706 28.819729 z\"\n"
  "       sodipodi:ry=\"3.0935922\"\n"
  "       sodipodi:rx=\"4.6845822\"\n"
  "       sodipodi:cy=\"28.819729\"\n"
  "       sodipodi:cx=\"43.045124\"\n"
  "       id=\"path19445\"\n"
  "       style=\"color:#000000;fill:#cbcbcb;fill-opacity:1.0000000;"
  "fill-rule:evenodd;stroke:none;stroke-width:2.2343740;stroke-linecap:butt;"
  "stroke-linejoin:miter;marker:none;marker-start:none;marker-mid:none;"
  "marker-end:none;stroke-miterlimit:4.0000000;stroke-dashoffset:0.0000000;"
  "stroke-opacity:1.0000000;visibility:visible;display:inline;"
  "overflow:visible\"\n"
  "       sodipodi:type=\"arc\" />\n"
  "    <path\n"
  "       sodipodi:type=\"arc\"\n"
  "       style=\"color:#000000;fill:url(#radialGradient19161);"
  "fill-opacity:1.0000000;fill-rule:evenodd;stroke:none;stroke-width:2.0000000;"
  "stroke-linecap:butt;stroke-linejoin:miter;marker:none;marker-start:none;"
  "marker-mid:none;marker-end:none;stroke-miterlimit:4.0000000;"
  "stroke-dashoffset:0.0000000;stroke-opacity:1.0000000;visibility:visible;"
  "display:inline;overflow:visible\"\n"
  "       id=\"path19145\"\n"
  "       sodipodi:cx=\"25.571428\"\n"
  "       sodipodi:cy=\"23.714285\"\n"
  "       sodipodi:rx=\"18.285715\"\n"
  "       sodipodi:ry=\"11.428572\"\n"
  "       d=\"M 43.857143 23.714285 A 18.285715 11.428572 0 1 1  7.2857132,"
  "23.714285 A 18.285715 11.428572 0 1 1  43.857143 23.714285 z\"\n"
  "       transform=\"translate(-1.517853,-5.266059)\" />\n"
  "    <path\n"
  "       sodipodi:type=\"arc\"\n"
  "       style=\"color:#000000;fill:url(#radialGradient19155);"
  "fill-opacity:1.0000000;fill-rule:evenodd;stroke:none;stroke-width:2.0000000;"
  "stroke-linecap:butt;stroke-linejoin:miter;marker:none;marker-start:none;"
  "marker-mid:none;marker-end:none;stroke-miterlimit:4.0000000;"
  "stroke-dashoffset:0.0000000;stroke-opacity:1.0000000;visibility:visible;"
  "display:inline;overflow:visible\"\n"
  "       id=\"path19147\"\n"
  "       sodipodi:cx=\"26.214285\"\n"
  "       sodipodi:cy=\"28.071428\"\n"
  "       sodipodi:rx=\"9.2142859\"\n"
  "       sodipodi:ry=\"5.0714288\"\n"
  "       d=\"M 35.428571 28.071428 A 9.2142859 5.0714288 0 1 1  16.999999,"
  "28.071428 A 9.2142859 5.0714288 0 1 1  35.428571 28.071428 z\"\n"
  "       transform=\"matrix(0.901236,0.000000,0.000000,1.028170,0.552644,"
  "-6.002357)\" />\n"
  "    <path\n"
  "       style=\"color:#000000;fill:#ffffff;fill-opacity:0.85964912;"
  "fill-rule:evenodd;stroke:none;stroke-width:2.0000000;stroke-linecap:butt;"
  "stroke-linejoin:miter;marker:none;marker-start:none;marker-mid:none;"
  "marker-end:none;stroke-miterlimit:4.0000000;stroke-dashoffset:0.0000000;"
  "stroke-opacity:1.0000000;visibility:visible;display:inline;"
  "overflow:visible\"\n"
  "       d=\"M 38.839286,11.785714 C 50.385742,23.087751 25.849808,36.998739 "
  "8.2767858,24.129464 C 11.435650,27.555058 17.281735,29.879464 24.058036,"
  "29.879464 C 34.151751,29.879464 42.339285,24.750535 42.339286,18.441964 C "
  "42.339286,15.943648 41.018131,13.667046 38.839286,11.785714 z \"\n"
  "       id=\"path19245\"\n"
  "       sodipodi:nodetypes=\"ccccc\" />\n"
  "    <path\n"
  "       sodipodi:type=\"arc\"\n"
  "       style=\"color:#000000;fill:url(#radialGradient19480);"
  "fill-opacity:1.0000000;fill-rule:evenodd;stroke:none;stroke-width:4.0000000;"
  "stroke-linecap:butt;stroke-linejoin:miter;marker:none;marker-start:none;"
  "marker-mid:none;marker-end:none;stroke-miterlimit:4.0000000;"
  "stroke-dashoffset:0.0000000;stroke-opacity:1.0000000;visibility:visible;"
  "display:inline;overflow:visible\"\n"
  "       id=\"path19472\"\n"
  "       sodipodi:cx=\"40.614445\"\n"
  "       sodipodi:cy=\"25.195807\"\n"
  "       sodipodi:rx=\"2.7842331\"\n"
  "       sodipodi:ry=\"1.6793786\"\n"
  "       d=\"M 43.398678 25.195807 A 2.7842331 1.6793786 0 1 1  37.830212,"
  "25.195807 A 2.7842331 1.6793786 0 1 1  43.398678 25.195807 z\"\n"
  "       transform=\"matrix(0.795827,0.000000,0.000000,0.947763,9.518711,"
  "3.245336)\" />\n"
  "    <path\n"
  "       transform=\"matrix(0.795827,0.000000,0.000000,0.947763,-24.91284,"
  "3.245336)\"\n"
  "       d=\"M 43.398678 25.195807 A 2.7842331 1.6793786 0 1 1  37.830212,"
  "25.195807 A 2.7842331 1.6793786 0 1 1  43.398678 25.195807 z\"\n"
  "       sodipodi:ry=\"1.6793786\"\n"
  "       sodipodi:rx=\"2.7842331\"\n"
  "       sodipodi:cy=\"25.195807\"\n"
  "       sodipodi:cx=\"40.614445\"\n"
  "       id=\"path19486\"\n"
  "       style=\"color:#000000;fill:url(#radialGradient19488);"
  "fill-opacity:1.0000000;fill-rule:evenodd;stroke:none;stroke-width:4.0000000;"
  "stroke-linecap:butt;stroke-linejoin:miter;marker:none;marker-start:none;"
  "marker-mid:none;marker-end:none;stroke-miterlimit:4.0000000;"
  "stroke-dashoffset:0.0000000;stroke-opacity:1.0000000;visibility:visible;"
  "display:inline;overflow:visible\"\n"
  "       sodipodi:type=\"arc\" />\n"
  "    <path\n"
  "       transform=\"matrix(0.672594,0.000000,0.000000,0.801003,12.18531,"
  "-11.02710)\"\n"
  "       d=\"M 43.398678 25.195807 A 2.7842331 1.6793786 0 1 1  37.830212,"
  "25.195807 A 2.7842331 1.6793786 0 1 1  43.398678 25.195807 z\"\n"
  "       sodipodi:ry=\"1.6793786\"\n"
  "       sodipodi:rx=\"2.7842331\"\n"
  "       sodipodi:cy=\"25.195807\"\n"
  "       sodipodi:cx=\"40.614445\"\n"
  "       id=\"path19490\"\n"
  "       style=\"color:#000000;fill:url(#radialGradient19494);"
  "fill-opacity:1.0000000;fill-rule:evenodd;stroke:none;stroke-width:4.0000000;"
  "stroke-linecap:butt;stroke-linejoin:miter;marker:none;marker-start:none;"
  "marker-mid:none;marker-end:none;stroke-miterlimit:4.0000000;"
  "stroke-dashoffset:0.0000000;stroke-opacity:1.0000000;visibility:visible;"
  "display:inline;overflow:visible\"\n"
  "       sodipodi:type=\"arc\" />\n"
  "    <path\n"
  "       sodipodi:type=\"arc\"\n"
  "       style=\"color:#000000;fill:url(#radialGradient19496);"
  "fill-opacity:1.0000000;fill-rule:evenodd;stroke:none;stroke-width:4.0000000;"
  "stroke-linecap:butt;stroke-linejoin:miter;marker:none;marker-start:none;"
  "marker-mid:none;marker-end:none;stroke-miterlimit:4.0000000;"
  "stroke-dashoffset:0.0000000;stroke-opacity:1.0000000;visibility:visible;"
  "display:inline;overflow:visible\"\n"
  "       id=\"path19492\"\n"
  "       sodipodi:cx=\"40.614445\"\n"
  "       sodipodi:cy=\"25.195807\"\n"
  "       sodipodi:rx=\"2.7842331\"\n"
  "       sodipodi:ry=\"1.6793786\"\n"
  "       d=\"M 43.398678 25.195807 A 2.7842331 1.6793786 0 1 1  37.830212,"
  "25.195807 A 2.7842331 1.6793786 0 1 1  43.398678 25.195807 z\"\n"
  "       transform=\"matrix(0.672594,0.000000,0.000000,0.801003,-17.56469,"
  "-11.02710)\" />\n"
  "    <path\n"
  "       style=\"color:#000000;fill:none;fill-opacity:1.0000000;"
  "fill-rule:evenodd;stroke:url(#linearGradient2503);stroke-width:0.96009976;"
  "stroke-linecap:butt;stroke-linejoin:miter;marker:none;marker-start:none;"
  "marker-mid:none;marker-end:none;stroke-miterlimit:4.0000000;"
  "stroke-dashoffset:0.0000000;stroke-opacity:1.0000000;visibility:visible;"
  "display:inline;overflow:visible\"\n"
  "       d=\"M 24.083697,6.1675499 C 20.071099,6.1675499 16.081300,7.0687304 "
  "12.972569,8.3627650 C 12.340267,8.0655819 11.677000,7.7627027 10.842347,"
  "7.7627026 C 8.7066143,7.7627026 7.0969450,8.7775783 7.0969451,10.187968 C "
  "7.0969451,10.684216 7.4808101,11.145939 7.8520106,11.538108 C 5.7184893,"
  "13.499999 4.0866584,15.859547 4.0866584,18.408822 C 4.0866584,20.339583 "
  "5.2278297,22.654171 6.5018703,24.279380 C 5.2536034,24.807385 4.0266521,"
  "25.688725 4.0266521,26.739635 C 4.0266521,28.379162 6.3894044,29.709945 "
  "8.8721166,29.709944 C 9.2303414,29.709944 9.5581218,29.612263 9.8922226,"
  "29.559928 C 9.7859219,29.915772 9.6822007,30.269380 9.6822007,30.640041 C "
  "9.6822005,31.308068 9.6822007,32.133034 9.6822007,32.801061 C 9.6822005,"
  "36.844777 16.239985,40.121820 24.293719,40.121821 C 32.347453,40.121822 "
  "38.875234,36.844776 38.875234,32.801061 C 38.875234,32.131408 38.875234,"
  "31.309694 38.875234,30.640041 C 38.875234,30.248011 38.783363,29.875253 "
  "38.665212,29.499922 C 39.172421,29.630935 39.708157,29.709944 40.285380,"
  "29.709944 C 42.768092,29.709944 45.160848,28.379162 45.160848,26.739635 C "
  "45.160848,25.474359 43.564518,24.407074 41.875546,23.979349 C 43.009758,"
  "22.429135 43.925733,20.223874 43.925733,18.408822 C 43.925733,16.067993 "
  "42.589187,13.909281 40.765430,12.048161 C 41.494617,11.583394 41.965555,"
  "10.909554 41.965555,10.187968 C 41.965555,8.7775779 40.855884,7.7627028 "
  "38.720153,7.7627026 C 37.632877,7.7627026 36.662961,8.0654250 35.959866,"
  "8.5427837 C 32.768041,7.1365188 28.282911,6.1675498 24.083697,6.1675499 z "
  "\"\n"
  "       id=\"path2495\"\n"
  "       sodipodi:nodetypes=\"ccccccccccccccccccccccccc\" />\n"
  "  </g>\n"
  "</svg>\n"
  "\n"
;
  return data::create<juce::Drawable>(data, arraysize(data));
};

}  // namespace icon
}  // namespace gui
}  // namespace rec
