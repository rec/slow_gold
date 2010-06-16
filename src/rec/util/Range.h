#ifndef __REC_UTIL_RANGE__
#define __REC_UTIL_RANGE__

namespace rec {
namespace util {

template <typename Items>
struct Range {
  Items begin_;
  Items end_;

  int64 length() const { return end_ - begin_; }
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_RANGE__
