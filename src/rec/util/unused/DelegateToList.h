#pragma once

#include "rec/base/base.h"

namespace rec {
namespace util {

template <typename Method, typename HasMethod, typename Iterator, typename Return>
Return delegateToList(Method method, HasMethod hasMethod,
                      Iterator begin, Iterator end, Return dflt) {
  for (Iterator i = begin; i != end; ++i) {
    if (*i && ((*i)->*hasMethod)())
      return ((*i)->*method)();
  }

  return dflt;
}

}  // namespace util
}  // namespace rec

