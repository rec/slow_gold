#include "{header_file}"

#include "rec/base/ArraySize.h"
#include "rec/util/Binary.h"

{namespace}

{datatype}* {classname}::create() {{
  static const char data[] = {data};
  return createBinary<{datatype}>(data, arraysize(data));
}};

{namespace_end}
