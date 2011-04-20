#include "{header_file}"
#include "rec/base/ArraySize.h"
#include "rec/gui/icon/Icon.h"

{namespace}

using juce::Drawable;

// Original command line: {cmd} {args}

Drawable* {classname}::get() {{
  static const char data[] = {svg};

  static Drawable* d = createFromImageData(data, arraysize(data));
  return d;
}};

{namespace_end}
