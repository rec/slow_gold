#include "rec/util/Callback.h"

namespace rec {
namespace util {

namespace {

class Foo {
 public:
  Foo() {}
  double MemberFunction(int a, int b)            { return a+b; }
  double ConstMemberFunction(int a, int b) const { return a-b; }
  static double StaticFunction(int a, int b)     { return a*b; }
};

double GlobalFunction(int a, int b) { return a/(double)b; }

struct Bar {
  double operator()(int a, int b) { return a + 2.0 * b; }
};

}  // namespace

TEST(Callback, All) {
}

void Invoke(int a, int b, Callback<double (int, int)> callback) {
  if(callback)
    {
        ::printf("%f\n", callback(a, b));
    }
    else
    {
        ::printf("Nothing to call.\n");
    }
}

int main()
{
    Foo f;
    Invoke(10, 20, BIND_MEM_CB(&Foo::MemberFunction, &f));
    Invoke(10, 20, BIND_MEM_CB(&Foo::ConstMemberFunction, &f));
    Invoke(10, 20, BIND_FREE_CB(&Foo::StaticFunction));

    Callback<double (int, int)> cb = BIND_FREE_CB(&GlobalFunction);
    Invoke(10, 20, cb);

    Bar bar;
    cb = BIND_MEM_CB(&Bar::operator(), &bar);
    Invoke(10, 20, cb);

    cb = util::NullCallback();
    Invoke(10, 20, cb);

    /* Expected output:
        30.000000
        -10.000000
        200.000000
        0.500000
        50.000000
        Nothing to call.
    */

    return 0;
}

}  // namespace util
}  // namespace rec
