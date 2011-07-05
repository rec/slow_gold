#include "{header_file}"

#include "rec/base/ArraySize.h"
#include "rec/data/Binary.h"

{namespace}

{datatype}* {classname}::create() {{
  static const char data[] = {data};
  return data::create<{datatype}>(data, arraysize(data));
}};

{namespace_end}
