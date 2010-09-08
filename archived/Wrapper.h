#ifndef __REC_UTIL_WRAPPER
#define __REC_UTIL_WRAPPER

namespace rec {
namespace util {

template <typename Wrapped>
class Wrapper : public Wrapped {
 public:
  explicit Wrapper(Wrapped* source = NULL) : source_(source) {}

  void setSource(Wrapped* source) { source_ = source; }

 protected:
  Wrapped* source_;
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_WRAPPER
