#ifndef __REC_UTIL_NOTIFIER
#define __REC_UTIL_NOTIFIER

namespace rec {
namespace util {

template <typename Value>
class Notifier {
 public:
  virtual void operator()(Value value) const = 0;
  virtual ~Notifier() {}
};

template <typename Value, typename Op>
class NotifierTemplate : public Notifier<Value> {
 public:
  NotifierTemplate(Op op) : op_(op) {}
  virtual void operator()(Value value) const { op_(value); }

 private:
  Op op_;
};


}  // namespace util
}  // namespace rec

#endif __REC_UTIL_NOTIFIER
