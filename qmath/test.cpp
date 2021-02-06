#include <stdio.h>
#include "qmath.hpp"

typedef Q<int32_t,int64_t,16> fixed;

#define F(val) fixed::from_float(val)
#define I(val) fixed::from_int(val)

int main() {

    fixed t1 = F(100) / F(-12);
    t1 *= I(2);
    printf("t1 = %f\n", t1.to_float());

    fixed foo = fixed::from_float(10.25f);
    fixed bar = fixed::from_float(-10.5f);
    fixed baz = foo + bar;

    fixed a = F(16.25);
    fixed b = F(10000.0);
    printf("a / b = %f\n", (a/b).to_float());

    printf("bits=%d, scale=%d, mask=%d\n", fixed::bits, fixed::scale, fixed::mask);

    printf("foo=%d\n", foo.raw);
    printf("bar=%d\n", bar.raw);
    printf("baz=%d\n", baz.raw);

    printf("answer(f)=%f\n", baz.to_float());
    printf("answer(i)=%d\n", baz.to_int());

    // baz *= 5;

    // printf("answer=%f\n", baz.to_float());

}