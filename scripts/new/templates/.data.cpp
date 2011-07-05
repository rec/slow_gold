#include "{header_file}"

#include "rec/base/ArraySize.h"
#include "rec/data/Binary.h"

{namespace}

// Automatically generated on {timestamp}
// from {sourcefile}

{datatype}* {classname}::create() {{
  static const char data[] = {data};
  return data::create<{datatype}>(data, arraysize(data));
}};

{namespace_end}
