#ifndef __REC_WIDGET_TREE_VIRTUALFILE__
#define __REC_WIDGET_TREE_VIRTUALFILE__

#include "rec/base/base.h"

namespace rec {
namespace widget {
namespace tree {

class VolumeFile;
class Volume;

const File getVolume(const Volume& v);
const File getFile(const VolumeFile& file);

const File getShadowVolume(const Volume& v);
const File getShadowFile(const VolumeFile& file);

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_VIRTUALFILE__
