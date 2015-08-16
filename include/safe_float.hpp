// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#pragma STDC FENV_ACCESS ON

#ifndef BOOST_NUMERIC_SAFE_FLOAT_HPP
#define BOOST_NUMERIC_SAFE_FLOAT_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <cfenv>
#include <cmath>
#include <type_traits>
#include <iostream>

//#include "exception_policies.hpp"

//forward_declarations
namespace boost {
namespace numeric {
    template <typename T, int P, typename E> class safe_float;
}
}
namespace std{
    template <typename T, int P, typename E>
    boost::numeric::safe_float<T, P, E> atanh(const boost::numeric::safe_float<T, P, E>& sf);

    template <typename T, int P, typename E>
    istream& operator>>(istream &is, boost::numeric::safe_float<T, P, E>& sf);

    template <typename T, int P, typename E>
    ostream& operator<<(std::ostream &os, const boost::numeric::safe_float<T, P, E>& sf);
}

namespace boost {
namespace numeric {
const int SF_INEXACT = 1;
const int SF_OVERFLOW = 2;
const int SF_UNDERFLOW = 4;
const int SF_DIV_BY_ZERO = 8;
const int SF_INVALID = 16; //nan & FE_INVALID
const int SF_DOMAIN = 32;
const int SF_POLE = 64;
const int SF_RANGE = 128;
const int SF_FLOAT_CAST = 256;
const int SF_INT_CAST = 512;
const int SF_INF_ON_ISTREAM = 1024;

const int SF_ALL = 2048-1 ;

//placeholder until exception_policies.hpp does not break compilation when included.
class throw_exception{};
//In the mean time errors catched at runtime are always reported by throwing.

template <
    typename T,
    int P = SF_ALL,
    typename E = throw_exception
>
class safe_float{
    T value;
    constexpr int sf_to_fe_flags(const int& flag) const{
        int rv = 0;
        if (SF_INEXACT & flag) rv |= FE_INEXACT;
        if (SF_OVERFLOW & flag) rv |= FE_OVERFLOW;
        if (SF_UNDERFLOW & flag) rv |= FE_UNDERFLOW;
        if (SF_DIV_BY_ZERO & flag) rv |= FE_DIVBYZERO;
        if (SF_INVALID & flag) rv |= FE_INVALID;
        return rv;
    }

public:
    //constructors
    //empty
    safe_float() : value(T(0)){
        static_assert(std::is_floating_point<T>::value, "safe_float wraps only floating point types");
    }
    //integers
    safe_float(int i) : value(i){
        static_assert(std::is_floating_point<T>::value, "safe_float wraps only floating point types");
        if ( i != (int) value ) throw std::exception();
    }

    safe_float(long int li) : value(li){
        static_assert(std::is_floating_point<T>::value, "safe_float wraps only floating point types");
        if ( li != (int) value ) throw std::exception();
    }

    safe_float(long long int lli){
        static_assert(std::is_floating_point<T>::value, "safe_float wraps only floating point types");
        value = lli;
        if ( lli != (long long int) value ) throw std::exception();
    }

    //T
    safe_float(T f) : value(f){
        static_assert(std::is_floating_point<T>::value, "safe_float wraps only floating point types");
        if (f != (T) value) throw std::exception();
        if (std::fpclassify( f ) == FP_SUBNORMAL ) throw std::exception();
    }

    //other floats
    template<typename U = T>
    safe_float(float f, typename std::enable_if<! std::is_same<U, float>::value>::type* = 0) : value(f) {
        static_assert(std::is_floating_point<T>::value, "safe_float wraps only floating point types");
        if ( f != (float) value ) throw std::exception();
        if (std::fpclassify( f ) == FP_SUBNORMAL ) throw std::exception();
    }

    template<typename U = T>
    safe_float(double d, typename std::enable_if<! std::is_same<U, double>::value>::type* = 0) : value(d) {
        static_assert(std::is_floating_point<T>::value, "safe_float wraps only floating point types");
        if ( d != (double) value ) throw std::exception();
        if (std::fpclassify( d ) == FP_SUBNORMAL ) throw std::exception();
    }

    template<typename U = T>
    safe_float(long double ld, typename std::enable_if<! std::is_same<U, long double>::value>::type* = 0) : value(ld) {
        static_assert(std::is_floating_point<T>::value, "safe_float wraps only floating point types");
        if ( ld != (long double) value ) throw std::exception();
        if (std::fpclassify( ld ) == FP_SUBNORMAL ) throw std::exception();
    }

//    //casting operator
//    operator int() {
//        int tmp = (int) value;
//        if (value != (float) tmp) throw std::exception();
//        return tmp;
//    }

    //unary arithmetic operators
    safe_float& operator+=(const safe_float &rhs) {
        //prepare
        feclearexcept(sf_to_fe_flags(P));

        //operate
        T tmp = value + rhs.value;

        //check result
        if (fetestexcept(sf_to_fe_flags(P))) throw std::exception();
        if (std::fpclassify( tmp ) == FP_SUBNORMAL) throw std::exception();
        if ((P | SF_INVALID) && isnan(tmp)) throw std::exception();

        //safe to assign and return
        value = tmp;
        return *this;
    }

    safe_float& operator-=(const safe_float& rhs) {
        //prepare
        feclearexcept(sf_to_fe_flags(P));

        //operate
        T tmp = value - rhs.value;

        //check result
        if (fetestexcept(sf_to_fe_flags(P))) throw std::exception();
        if (std::fpclassify( tmp ) == FP_SUBNORMAL) throw std::exception();
        if ((P | SF_INVALID) && isnan(tmp)) throw std::exception();

        //safe to assign and return
        value = tmp;
        return *this;
    }

    safe_float& operator*=(const safe_float& rhs) {
        //prepare
        feclearexcept(sf_to_fe_flags(P));

        //operate
        T tmp = value * rhs.value;

        //check result
        if (fetestexcept(sf_to_fe_flags(P))) throw std::exception();
        if (std::fpclassify( tmp ) == FP_SUBNORMAL) throw std::exception();
        if ((P | SF_INVALID) && isnan(tmp)) throw std::exception();

        //safe to assign and return
        value = tmp;
        return *this;
    }

    safe_float& operator/=(const safe_float& rhs) {
        //prepare
        feclearexcept(sf_to_fe_flags(P));

        //check domain
        if (rhs.value == 0) throw std::exception();

        //operate
        T tmp = value / rhs.value;

        //check result
        if (fetestexcept(sf_to_fe_flags(P))) throw std::exception();
        if (std::fpclassify( tmp ) == FP_SUBNORMAL) throw std::exception();
        if ((P | SF_INVALID) && isnan(tmp)) throw std::exception();

        //safe to assign and return
        value = tmp;
        return *this;
    }

    safe_float& operator-(){
        //prepare
        feclearexcept(sf_to_fe_flags(P));

        //operate
        T tmp = -value;

        //check result
        if (fetestexcept(sf_to_fe_flags(P))) throw std::exception();

        //safe assign and return
        value = tmp;
        return *this;
    }

    //comparison operators
    bool operator==(const safe_float& rhs) const{
        return (value == rhs.value);
    }

    bool operator<(const safe_float& rhs) const{
        return (value < rhs.value);
    }

    //math.h friends
    friend safe_float std::atanh<T, P, E>(const safe_float& sf);

    //iostream friends
    friend std::istream& std::operator>> <T, P, E>(std::istream &is, safe_float& sf);
    friend std::ostream& std::operator<< <T, P, E>(std::ostream &os, const safe_float& sf);
};

//binary arithmetic opertors
template<typename T, int P, typename E>
safe_float<T, P, E> operator+(safe_float<T, P, E> lhs, const safe_float<T, P, E>& rhs) {
    lhs += rhs;
    return lhs;
}

template<typename T, int P, typename E>
safe_float<T, P, E> operator-(safe_float<T, P, E> lhs, const safe_float<T, P, E>& rhs) {
    lhs -= rhs;
    return lhs;
}

template<typename T, int P, typename E>
safe_float<T, P, E> operator*(safe_float<T, P, E> lhs, const safe_float<T, P, E>& rhs) {
    lhs *= rhs;
    return lhs;
}

template<typename T, int P, typename E>
safe_float<T, P, E> operator/(safe_float<T, P, E> lhs, const safe_float<T, P, E>& rhs) {
    lhs /= rhs;
    return lhs;
}


//comparison operators
template<typename T, int P, typename E>
inline bool operator!=(const safe_float<T, P, E>& lhs, const safe_float<T, P, E>& rhs){
    return !(lhs == rhs);
}

template<typename T, int P, typename E>
inline bool operator> (const safe_float<T, P, E>& lhs, const safe_float<T, P, E>& rhs){
    return rhs < lhs;
}

template<typename T, int P, typename E>
inline bool operator<=(const safe_float<T, P, E>& lhs, const safe_float<T, P, E>& rhs){
    return !(lhs > rhs);
}

template<typename T, int P, typename E>
inline bool operator>=(const safe_float<T, P, E>& lhs, const safe_float<T, P, E>& rhs){
    return !(lhs < rhs);
}

} // numeric
} // boost

namespace std {

template <typename T, int P, typename E>
istream& operator>>(istream &is, boost::numeric::safe_float<T, P, E>& sf){
    T tmp;
    is >> tmp;

    std::cout << tmp << std::endl;
    if ((P | boost::numeric::SF_INVALID) && isnan(tmp)) throw std::exception();
    if ( (boost::numeric::SF_INF_ON_ISTREAM & P) && isinf(tmp) ) throw exception();

    sf.value = tmp;
    return is;
}

template <typename T, int P, typename E>
ostream& operator<<(ostream &os, const boost::numeric::safe_float<T, P, E>& sf){
    os << sf.value;
    return os;
}

//safe_float<F> has same numeric limits than F, but has not NAN and no denorm representations
template <typename FP, int P, typename E>
class numeric_limits<boost::numeric::safe_float<FP, P, E>>{
    using number_type = boost::numeric::safe_float<FP, P, E>;
public:
   static constexpr bool is_specialized = true;
   static constexpr int digits = std::numeric_limits<FP>::digits;
   static constexpr int digits10 = std::numeric_limits<FP>::digits10;
   static constexpr int max_digits10 = std::numeric_limits<FP>::max_digits10;
   static constexpr bool is_signed = std::numeric_limits<FP>::is_signed;
   static constexpr bool is_integer = std::numeric_limits<FP>::is_integer;
   static constexpr int radix = std::numeric_limits<FP>::radix;
   static constexpr int min_exponent = std::numeric_limits<FP>::min_exponent;
   static constexpr int min_exponent10 = std::numeric_limits<FP>::min_exponent10;
   static constexpr int max_exponent = std::numeric_limits<FP>::max_exponent;
   static constexpr int max_exponent10 = std::numeric_limits<FP>::max_exponent10;
   static constexpr bool has_infinity = std::numeric_limits<FP>::has_infinity;
   static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
   static constexpr bool has_denorm_loss = std::numeric_limits<FP>::has_denorm_loss;
   static constexpr bool is_iec559 = std::numeric_limits<FP>::is_iec559;
   static constexpr bool is_bounded = std::numeric_limits<FP>::is_bounded;
   static constexpr bool is_modulo = std::numeric_limits<FP>::is_modulo;
   static constexpr bool traps = std::numeric_limits<FP>::traps;
   static constexpr bool tinyness_before = std::numeric_limits<FP>::tinyness_before;

   static constexpr bool is_exact = std::numeric_limits<FP>::is_exact;
   static constexpr bool has_quiet_NaN = false;
   static constexpr bool has_signaling_NaN = false;
   static constexpr float_round_style round_style = std::numeric_limits<FP>::round_style;

   static constexpr number_type min() noexcept(std::numeric_limits<FP>::min()){
       return number_type(std::numeric_limits<FP>::min());
   }
   static constexpr number_type max() noexcept(std::numeric_limits<FP>::max()){
       return number_type(std::numeric_limits<FP>::max());
   }
   static constexpr number_type lowest() noexcept(max){
       return -(max)();
   }
   static constexpr number_type epsilon() noexcept(std::numeric_limits<FP>::epsilon()){
       return  number_type(std::numeric_limits<FP>::epsilon());
   }
   static constexpr number_type round_error() noexcept(std::numeric_limits<FP>::round_error()){
       return  number_type(std::numeric_limits<FP>::round_error());
   }
   static constexpr number_type infinity() noexcept(std::numeric_limits<FP>::infinity()){
       return  number_type(std::numeric_limits<FP>::infinity());
   }
   static constexpr number_type quiet_NaN() noexcept(std::numeric_limits<FP>::quiet_NaN()){
       return  number_type(std::numeric_limits<FP>::quiet_NaN());
   }
   static constexpr number_type signaling_NaN() noexcept(std::numeric_limits<FP>::signaling_NaN()){
       return  number_type(std::numeric_limits<FP>::signaling_NaN());
   }
   static number_type denorm_min() noexcept(std::numeric_limits<FP>::denorm_min()){
       return  number_type(std::numeric_limits<FP>::denorm_min());
   }
};



}

#endif // BOOST_NUMERIC_SAFE_FLOAT_HPP
