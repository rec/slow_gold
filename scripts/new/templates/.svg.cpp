#include "{header_file}"
#include "rec/base/ArraySize.h"
#include "rec/gui/icon/Icon.h"

{namespace}

using juce::Drawable;

// Created by the command line:
// {commandline}

Drawable* {classname}::get() {{
  static const char data[] = {data};

  static Drawable* d = createFromImageData(data, arraysize(data));
  return d;
}};

{namespace_end}
