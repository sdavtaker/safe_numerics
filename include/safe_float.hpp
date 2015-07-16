// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_NUMERIC_SAFE_FLOAT_HPP
#define BOOST_NUMERIC_SAFE_FLOAT_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

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
    boost::numeric::safe_float<T, P, E> acos(const boost::numeric::safe_float<T, P, E>& sf);
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
    safe_float(T f) : value(f){}


    //math.h friends
    friend safe_float std::acos<T, P, E>(const safe_float& sf);
};

} // numeric
} // boost


#endif // BOOST_NUMERIC_SAFE_FLOAT_HPP
