#pragma once

#include "rec/data/Data.h"
#include "rec/util/proto/Proto.h"

namespace rec {
namespace data {

template <typename Proto>
void apply(void (*function)(Proto*), const VirtualFile& vf) {
    function(Opener<Proto>(getData(getTypeName<Proto>(), vf)).mutable_get());
}

template <typename Proto, typename Functor>
void apply(Functor functor, const VirtualFile& vf) {
    functor(Opener<Proto>(getData(getTypeName<Proto>(), vf)).mutable_get());
}

template <typename Proto>
bool applyToData(bool (*function)(Proto*), Data* data) {
    return function(Opener<Proto>(data).mutable_get());
}

template <typename Proto, typename Functor>
bool applyToData(Functor functor, Data* data) {
    return functor(Opener<Proto>(data).mutable_get());
}

}  // namespace data
}  // namespace rec

