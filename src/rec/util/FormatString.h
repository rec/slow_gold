#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {

class FormatString {
 public:
  FormatString(const String&);

  String format(const juce::StringArray&) const;

  String format() const;
  String format(const String&) const;
  String format(const String&, const String&) const;
  String format(const String&, const String&, const String&) const;

 private:
  juce::StringArray parts_;
  juce::Array<int> args_;

  DISALLOW_COPY_ASSIGN_AND_LEAKS(FormatString);
};

}  // namespace util
}  // namespace rec

