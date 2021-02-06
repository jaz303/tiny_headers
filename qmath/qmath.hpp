#ifndef JTH_QMATH_HPP_
#define JTH_QMATH_HPP_

#include <stdio.h>
#include <math.h>

/**
 * 
 * 
 * S  - Storage type for raw value.
 * MD - Intermediate storage type using during multiplication/division.
 *      Should be double the size of S.
 * B  - Number of bits for fractional part.
 * 
 * Commonly a typedef would be used:
 * 
 * typedef Q<int32_t,int64_t,16> fixed;
 */
template<class S, class MD, int B>
class Q {
public:
    static constexpr int bits = B;
    static constexpr int scale = (1 << B);
    static constexpr int mask = (1 << B) - 1;

    static Q from_float(float val) { return Q(S(val*scale)); }
    static Q from_double(double val) { return Q(S(val*scale)); }
    static Q from_int(int val) { return Q(S(val*scale)); }

    S raw;

    Q()         : raw(0) {}
    Q(S val)    : raw(val) {}

    Q operator+(const Q& rhs) { return Q(raw + rhs.raw); }
    Q operator-(const Q& rhs) { return Q(raw - rhs.raw); }
    Q operator*(const Q& rhs) { return Q((MD(raw) * rhs.raw) / scale); }
    Q operator/(const Q& rhs) { return Q((MD(raw) * scale) / rhs.raw); }

    Q& operator+=(const Q& rhs) { raw += rhs.raw; return *this; }
    Q& operator-=(const Q& rhs) { raw -= rhs.raw; return *this; }
    Q& operator*=(const Q& rhs) { raw = (MD(raw) * rhs.raw) / scale; return *this; }
    Q& operator/=(const Q& rhs) { raw = (MD(raw) * scale) / rhs.raw; return *this; }

    int to_int() const { return raw / scale; }
    float to_float() const { return double(raw)/scale; }
    double to_double() const { return double(raw)/scale; }
};

#endif