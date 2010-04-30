#ifndef __REC_UTIL_NOTIFIER
#define __REC_UTIL_NOTIFIER

namespace rec {
namespace util {

struct wtf {
};

class Notifier {
 public:
  Notifier() {}
  virtual void operator()() const = 0;
  virtual ~Notifier() {}
};

template <typename Op>
class NotifierTemplate : public Notifier {
 public:
  NotifierTemplate(Op op) : op_(op) {}
  virtual void operator()() const { op_(); }

 private:
  Op op_;
};


}  // namespace util
}  // namespace rec

#endif __REC_UTIL_NOTIFIER
