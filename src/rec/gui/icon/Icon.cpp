#include "rec/gui/icon/Icon.h"
#include "rec/gui/icon/OpenFolder.svg.h"
#include "rec/gui/icon/ThickFolder.svg.h"
#include "rec/gui/icon/ThinFolder.svg.h"
#include "rec/util/STL.h"

using namespace juce;

namespace rec {
namespace gui {
namespace icon {

namespace {

typedef std::map<string, const Drawable*> IconMap;

struct IconMapMaker {
  IconMap map_;
  IconMapMaker() {
    map_["OpenFolder"] = OpenFolder::get();
    map_["ThickFolder"] = ThickFolder::get();
    map_["ThinFolder"] = ThinFolder::get();
  }
};

}  // namespace

const Drawable* getIcon(const string& n) {
  if (n.empty())
    return NULL;

  static IconMapMaker* maker = new IconMapMaker();
  static IconMap& map = maker->map_;
  IconMap::const_iterator i = map.find(n);
  if (i != map.end())
    return i->second;

  LOG(ERROR) << "Couldn't find icon " << n;
  return NULL;
}


static std::vector<Drawable*> ICONS;

Drawable* createFromImageData(const char* data, int len) {
  Drawable* d = Drawable::createFromImageData(data, len);
  ICONS.push_back(d);

  return d;
}

void deleteIcons() {
  stl::deletePointers(&ICONS);
}


}  // namespace icon
}  // namespace gui
}  // namespace rec
