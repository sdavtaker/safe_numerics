#define BOOST_TEST_MODULE Main
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/list.hpp>

#include <safe_float.hpp>

//types to be tested
using test_types=boost::mpl::list<
    float, double, long double
>;

using namespace boost::numeric;

/**
  This test suite checks different policies on division operations using default parameters for the other policies.
  */
BOOST_AUTO_TEST_SUITE( safe_float_division_test_suite )
BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_division_divides, FPT, test_types){
    safe_float<FPT> a(33.0);
    safe_float<FPT> b(11.0);
    safe_float<FPT> c(3.0);
    BOOST_CHECK_EQUAL(a/b, c);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_division_throws_on_overflow, FPT, test_types){
    // define two FPT numbers suppose to positive overflow
    FPT a = std::numeric_limits<FPT>::max();
    FPT b = std::numeric_limits<FPT>::min();
    // check FPT overflows to inf after add
    BOOST_CHECK(isinf(a/b));

    // construct safe_float version of the same two numbers
    safe_float<FPT> c(a);
    safe_float<FPT> d(b);

    // check the division throws
    BOOST_CHECK_THROW(c/d, std::exception);

    // define two FPT numbers suppose to negative overflow
    FPT e = std::numeric_limits<FPT>::lowest();
    FPT f = std::numeric_limits<FPT>::min();
    // check FPT overflows to inf after add
    BOOST_CHECK(isinf(e/f));

    // construct safe_float version of the same two numbers
    safe_float<FPT> g(e);
    safe_float<FPT> h(f);

    // check the division throws
    BOOST_CHECK_THROW(g/h, std::exception);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_division_inexact_rounding, FPT, test_types){
    // define two FPT numbers suppose to produce inexact rounding
    FPT a = 1;
    FPT b = pow(3, std::numeric_limits<FPT>::digits);

    // check multiplying and dividing do not give the same number back.
    BOOST_CHECK((a/b)*b != a);

    // construct safe_float version of the same two numbers
    safe_float<FPT> c(a);
    safe_float<FPT> d(b);

    // check the division throws
    BOOST_CHECK_THROW(c/d, std::exception);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_division_underflow, FPT, test_types){
    // define two FPT numbers suppose to underflow
    FPT a = std::numeric_limits<FPT>::min();
    FPT b = std::numeric_limits<FPT>::max();

    // check dividing big numbers underflows to 0.
    BOOST_CHECK((a/b) == 0);

    // construct safe_float version of the same two numbers
    safe_float<FPT> c(a);
    safe_float<FPT> d(b);

    // check the division throws
    BOOST_CHECK_THROW(c/d, std::exception);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_division_invalid_result, FPT, test_types){
    // define two FPT numbers suppose to produce a NAN
    FPT a = std::numeric_limits<FPT>::infinity();
    FPT b = std::numeric_limits<FPT>::infinity();

    // check adding produced NaN
    BOOST_CHECK(isnan(a/b));

    // construct safe_float version of the same two numbers
    safe_float<FPT> c(a);
    safe_float<FPT> d(b);

    // check the division throws
    BOOST_CHECK_THROW(c/d, std::exception);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_division_by_zero, FPT, test_types){
    // construct safe_float producing divide by zero
    safe_float<FPT> c(1);
    safe_float<FPT> d(0);

    // check the division throws
    BOOST_CHECK_THROW(c/d, std::exception);
}


BOOST_AUTO_TEST_SUITE_END()

