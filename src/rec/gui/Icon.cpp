#include <glog/logging.h>

#include "rec/gui/Icon.h"
#include "rec/gui/tree/LeftArrow.svg.h"

using namespace juce;

namespace rec {
namespace gui {
  
namespace {

typedef std::map<string, const Drawable*> IconMap;

struct IconMapMaker {
  IconMap map_;
  IconMapMaker() {
    map_["LeftArrow"] = tree::LeftArrow::get();
  }
};

}  // namespace

const Drawable* getIcon(const string& n) {
  static IconMapMaker* maker = new IconMapMaker();
  static IconMap& map = maker->map_;
  IconMap::const_iterator i = map.find(n);
  if (i != map.end())
    return i->second;

  LOG(ERROR) << "Couldn't find icon " << n;
  return NULL;
}

}  // namespace gui
}  // namespace rec
