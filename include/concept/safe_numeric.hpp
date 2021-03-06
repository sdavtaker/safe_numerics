#ifndef BOOST_NUMERIC_CONCEPT_SAFE_NUMERIC_HPP
#define BOOST_NUMERIC_CONCEPT_SAFE_NUMERIC_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  Copyright (c) 2015 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <limits>
#include <typetraits>
#include <boost/concept/usage.hpp>
#include "numeric.hpp"

namespace boost {
namespace numeric {

template<class T>
struct SafeNumeric : public Numeric<T> {
    static_assert(
        is_safe<T>::value,
        "std::numeric_limits<T> has not been specialized for this type"
    );
    BOOST_CONCEPT_USAGE(SafeNumeric){
        typedef get_exception_policy<T> t1;
        typedef get_promotion_policy<T> t2;
        typedef base_type<T> t3;
    }
};

} // numeric
} // boost

#endif // BOOST_NUMERIC_CONCEPT_SAFE_NUMERIC_HPP
