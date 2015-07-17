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

#include <fenv.h>
#include <type_traits>
#include <iostream>

//#include "native.hpp"
//#include "exception_policies.hpp"

//forward_declarations
namespace boost {
namespace numeric {
    template <class T, class P, class E> class safe_float;
}
}
namespace std{
    template <class T, class P, class E>
    boost::numeric::safe_float<T, P, E> atanh(const boost::numeric::safe_float<T, P, E>& sf);

    template< class T, class P, class E>
    istream& operator>>(istream &is, boost::numeric::safe_float<T, P, E>& sf);
}

namespace boost {
namespace numeric {

class native{}; //placeholder until native.hpp does not break compilation when included.
class throw_exception{}; //placeholder until exception_policies.hpp does not break compilation when included.

template <
    class T,
    class P = native,
    class E = throw_exception
>
class safe_float{
    T value;
public:
    //constructors
    safe_float() : value(T(0)){}
    safe_float(T f) : value(f){
        if (std::fpclassify( f ) == FP_SUBNORMAL ) throw std::exception();
    }

    safe_float(int i) : value(i){
        if ( i != (int) value ) throw std::exception();
    }


    safe_float(double d, typename std::enable_if<! std::is_same<T, double>::value>::type* = 0) : value(d) {
        if ( d != (double) value ) throw std::exception();
    }

    //casting operator
    operator int() {
        int tmp = (int) value;
        if (value != (float) tmp) throw std::exception();
        return tmp;
    }

    //operators
    safe_float& operator+=(const safe_float &rhs) {
        safe_float<T, P, E> tmp;
        feclearexcept(FE_INEXACT);
        tmp.value = value + rhs.value;
        if (fetestexcept(FE_INEXACT)) throw std::exception();
        value = tmp.value;
        return *this;
    }

    //math.h friends
    friend safe_float std::atanh<T, P, E>(const safe_float& sf);
    friend std::istream& std::operator>> <T, P, E>(std::istream &is, safe_float& sf);
};

} // numeric
} // boost

namespace std {

template < class T, class P, class E>
istream& operator>>(istream &is, boost::numeric::safe_float<T, P, E>& sf){
    T tmp;
    is >> tmp;
    if (isnan(tmp)) throw exception();
    if (isinf(tmp)) throw exception();
    sf.value = tmp;
    return is;
}

}

#endif // BOOST_NUMERIC_SAFE_FLOAT_HPP
