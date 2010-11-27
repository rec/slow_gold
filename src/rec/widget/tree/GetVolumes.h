#ifndef __REC_WIDGET_TREE_GETVOLUMES__
#define __REC_WIDGET_TREE_GETVOLUMES__

#include <vector>

#include "rec/base/base.h"
#include "rec/widget/tree/VolumeFile.pb.h"

namespace rec {
namespace widget {
namespace tree {

typedef std::vector<Volume> VolumeList;

VolumeList getVolumes();

}  // namespace tree
}  // namespace widget
}  // namespace rec

#endif  // __REC_WIDGET_TREE_GETVOLUMES__
