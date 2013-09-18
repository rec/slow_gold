#ifndef __REC_GUI_PROTO_CONSTANTS__
#define __REC_GUI_PROTO_CONSTANTS__

#include <unordered_map>

#include "rec/base/base.h"

namespace rec {
namespace gui {

class ConstantProtos;

class Constants {
 public:
  Constants() {}
  Constants(const ConstantProtos&);
  double operator()(const string&);

 private:
  std::unordered_map<string, double> map_;
};

}  // namespace gui
}  // namespace rec

#endif  // __REC_GUI_PROTO_CONSTANTS__
