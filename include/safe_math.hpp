// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_NUMERIC_SAFE_MATH_HPP
#define BOOST_NUMERIC_SAFE_MATH_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <cmath>
#include "safe_float.hpp"

//This header file overloads <cmath> for safe_float types adding domain, pole and range error checking.
namespace std {
template < class T, class P, class E>
boost::numeric::safe_float<T, P, E> atanh(const boost::numeric::safe_float<T, P, E>& sf){

    if (math_errhandling & MATH_ERREXCEPT) {
        feclearexcept(FE_ALL_EXCEPT);
    }
    errno = 0;
    T tmp = atanh(sf.value);


    if (math_errhandling & MATH_ERRNO) {
        if (errno==EDOM) throw std::exception(); //domain error
        if (errno==ERANGE) throw std::exception(); //range error
    }
    if (math_errhandling  & MATH_ERREXCEPT) {
        if (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW) throw std::exception(); //pole error
    }

    return boost::numeric::safe_float<T, P, E>(tmp);

}

}

#endif // BOOST_NUMERIC_SAFE_MATH_HPP

