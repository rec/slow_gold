#ifndef __REC_UTIL_WRAPPER
#define __REC_UTIL_WRAPPER

namespace rec {
namespace util {

template <typename Wrapped>
class Wrapper : public Wrapped {
 public:
  Wrapper() : source_(NULL) {}

  void setSource(Wrapped* source) { source_ = source; }

 protected:
  Wrapped* source_;
};

}  // namespace util
}  // namespace rec

#endif  // __REC_UTIL_WRAPPER
