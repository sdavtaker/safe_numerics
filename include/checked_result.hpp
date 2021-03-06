//
//  checked_result.hpp
//  SafeIntegers
//
//  Created by Robert Ramey on 2/26/15.
//
//

#ifndef BOOST_NUMERIC_CHECKED_RESULT
#define BOOST_NUMERIC_CHECKED_RESULT

#include "safe_common.hpp" // SAFE_NUMERIC_CONSTEXPR
#include "exception_policies.hpp"

namespace boost {
namespace numeric {

template<typename R>
struct checked_result {
// poor man's variant which supports SAFE_NUMERIC_CONSTEXPR
    enum class exception_type {
        no_exception,
        overflow_error,
        underflow_error,
        range_error,
        domain_error,
        uninitialized
    };
    const exception_type m_e;
    const union {
        R m_r;
        char const * m_msg;
    };
    // constructors
    // breaks add/subtract etc.!!!
    // perhaps because defining a copy constructure suppresses implicite move?
    /*
    SAFE_NUMERIC_CONSTEXPR checked_result(const checked_result<R> & r) :
        m_e(r.m_e)
    {
        (m_e == exception_type::no_exception) ?
            (m_r = r.m_r), 0
        :
            (m_msg = r.m_msg), 0
        ;
    }
    // don't permit construction without initial value;
    SAFE_NUMERIC_CONSTEXPR explicit checked_result() :
        m_e(exception_type::uninitialized),
        m_r(0)
    {}
    */
    SAFE_NUMERIC_CONSTEXPR explicit checked_result(const R & r) :
        m_e(exception_type::no_exception),
        m_r(r)
    {}
    SAFE_NUMERIC_CONSTEXPR explicit checked_result(exception_type e, const char * msg) :
        m_e(e),
        m_msg(msg)
    {}
    // accesors
    SAFE_NUMERIC_CONSTEXPR operator R() const {
        return (exception_type::no_exception == m_e) ?
            m_r
        :
            0
        ;
    }
    SAFE_NUMERIC_CONSTEXPR operator exception_type() const {
        return m_e;
    }
    SAFE_NUMERIC_CONSTEXPR operator const char *() const {
        return m_msg;
    }
    SAFE_NUMERIC_CONSTEXPR bool operator<(const checked_result & r) const {
        return
            (m_e == exception_type::no_exception
            || r.m_e == exception_type::no_exception) ?
                false // replace with tribool?
            :
                m_r < r.m_r
            ;
    }
    SAFE_NUMERIC_CONSTEXPR bool operator==(const exception_type & et) const {
        return m_e == et;
    }
    SAFE_NUMERIC_CONSTEXPR bool operator!=(const exception_type & et) const {
        return m_e != et;
    }
    SAFE_NUMERIC_CONSTEXPR bool is_valid() const {
        return m_e == exception_type::no_exception;
    }

    template<class EP>
    void
    dispatch() const {
        BOOST_CONCEPT_ASSERT((ExceptionPolicy<EP>));
        switch(m_e){
        case exception_type::overflow_error:
            EP::overflow_error(m_msg);
            break;
        case checked_result<R>::exception_type::underflow_error:
            EP::underflow_error(m_msg);
            break;
        case checked_result<R>::exception_type::range_error:
            EP::range_error(m_msg);
            break;
        case checked_result<R>::exception_type::domain_error:
            EP::domain_error(m_msg);
            break;
        case checked_result<R>::exception_type::no_exception:
            break;
        default:
            break;
        }
    }
};

template<typename R>
SAFE_NUMERIC_CONSTEXPR inline const checked_result<R> min(
    const checked_result<R> & t,
    const checked_result<R> & u
){
    return
        (t.m_e == checked_result<R>::exception_type::no_exception
        && u.m_e == checked_result<R>::exception_type::no_exception) ?
            t.m_r < u.m_r ?
                t
            :
                u
        :
            checked_result<R>(
                checked_result<R>::exception_type::range_error,
                "Can't compare values without values"
            )
        ;
}

template<typename R>
SAFE_NUMERIC_CONSTEXPR inline const checked_result<R> max(const checked_result<R> & t, const checked_result<R> & u){
    return
        (t.m_e == checked_result<R>::exception_type::no_exception
        && u.m_e == checked_result<R>::exception_type::no_exception) ?
            t.m_r < u.m_r ?
                u
            :
                t
        :
            checked_result<R>(
                checked_result<R>::exception_type::range_error,
                "Can't compare values without values"
            )
        ;
}

} // numeric
} // boost

#include <ostream>

template<typename R>
std::ostream & operator<<(std::ostream & os, const boost::numeric::checked_result<R> & r){
    if(r == boost::numeric::checked_result<R>::exception_type::no_exception)
        os << static_cast<R>(r);
    else
        os << static_cast<const char *>(r);
    return os;
}


#endif  // BOOST_NUMERIC_CHECKED_CHECKED_RESULT
