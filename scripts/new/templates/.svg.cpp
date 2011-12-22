#include "{header_file}"
#include "rec/base/ArraySize.h"
#include "rec/util/Binary.h"

{namespace}

using juce::Drawable;

// Created by the command line:
// {commandline}

Drawable* {classname}::create() {{
  static const char data[] = {data};

  return createBinary<Drawable>(data, arraysize(data));
}};

{namespace_end}
