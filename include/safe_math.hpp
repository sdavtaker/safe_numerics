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
boost::numeric::safe_float<T, P, E> acos(const boost::numeric::safe_float<T, P, E>& sf){
        if (sf.value > 1 || sf.value < -1 ) throw std::exception();
        return boost::numeric::safe_float<T, P, E>(acos(sf.value));
    }
}


#endif // BOOST_NUMERIC_SAFE_MATH_HPP

