#ifndef __REC_YAML_YAML__
#define __REC_YAML_YAML__

#include "rec/base/BaseNoJuce.h"

namespace rec {
namespace yaml {

string write(const Message& from);
bool read(const string& from, Message* to);

}  // namespace yaml
}  // namespace rec

#endif  // __REC_YAML_YAML__
