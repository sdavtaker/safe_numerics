#ifndef BOOST_NUMERIC_CONCEPT_NUMERIC_HPP
#define BOOST_NUMERIC_CONCEPT_NUMERIC_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//  Copyright (c) 2012 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <limits>

namespace boost {
namespace numeric {

template<class T>
struct Numeric {
    // if your program traps here, you need to create a
    // std::numeric_limits class for your type T.  see
    // see C++ standard 18.3.2.2
    static_assert(
        std::numeric_limits<T>::is_specialized,
        "std::numeric_limits<T> has not been specialized for this type"
    );
    // verify that T is an integer type
    static_assert(
        std::numeric_limits<T>::is_integer,
        "T is not an integer type"
    );
};

template <class T>
class Integer : public Numeric<T> {
    // integer types must have the corresponding numeric trait.
    static_assert(
        std::numeric_limits<T>::is_integer,
        "integer types must have the corresponding numeric trait"
    );
};

} // numeric
} // boost

#endif // BOOST_NUMERIC_CONCEPT_NUMERIC_HPP
