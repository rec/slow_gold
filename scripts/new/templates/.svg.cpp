#include "{header_file}"
#include "rec/base/ArraySize.h"
#include "rec/util/Binary.h"

{namespace}

using juce::Drawable;

// Created by the command line:
// {commandline}

Drawable* {classname}::get() {{
  static const char data[] = {data};

  static Drawable* d = createBinary<Drawable>(data, arraysize(data));
  return d;
}};

{namespace_end}
