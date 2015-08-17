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

BOOST_AUTO_TEST_SUITE( safe_float_addition_test_suite )

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_addition_adds, FPT, test_types){
    safe_float<FPT> a(17.0);
    safe_float<FPT> b(23.0);
    safe_float<FPT> c(40.0);
    BOOST_CHECK_EQUAL(a+b, c);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_addition_throws_on_overflow, FPT, test_types){
    // define two FPT numbers suppose to positive overflow
    FPT a = std::numeric_limits<FPT>::max();
    FPT b = std::numeric_limits<FPT>::max();
    // check FPT overflows to inf after add
    BOOST_CHECK(isinf(a+b));

    // construct safe_float version of the same two numbers
    safe_float<FPT> c(a);
    safe_float<FPT> d(b);

    // check the addition throws

    BOOST_CHECK_THROW(c+d, std::exception);

    // define two FPT numbers suppose to negative overflow
    FPT e = std::numeric_limits<FPT>::lowest();
    FPT f = std::numeric_limits<FPT>::lowest();
    // check FPT overflows to inf after add
    BOOST_CHECK(isinf(e+f));

    // construct safe_float version of the same two numbers
    safe_float<FPT> g(e);
    safe_float<FPT> h(f);

    // check the addition throws
    BOOST_CHECK_THROW(g+h, std::exception);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_addition_inexact_rounding, FPT, test_types){
    // define two FPT numbers suppose to produce an inexact rounded result
    FPT a = 1;
    FPT b = std::numeric_limits<FPT>::max() / (FPT) 4;

    // check adding and substracting b does not obtain a again.
    BOOST_CHECK(a+b-b != a);
    // construct safe_float version of the same two numbers
    safe_float<FPT> c(a);
    safe_float<FPT> d(b);

    // check the addition throws
    BOOST_CHECK_THROW(c+d, std::exception);

}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_addition_underflow, FPT, test_types){
    // define two FPT numbers suppose to underflow
    FPT a, b, c;
    if (std::is_same<FPT, double>()) {
        a =  2.2250738585072019e-308;
        b = -2.2250738585072014e-308;
        //check the addition produces an denormal result (considered underflow)
        c = a + b;
        BOOST_CHECK( std::fpclassify( c ) == FP_SUBNORMAL ) ;

        // construct safe_float version of the same two numbers
        safe_float<FPT> d(2.2250738585072019e-308);
        safe_float<FPT> e(-2.2250738585072014e-308);

        // check the addition throws
        BOOST_CHECK_THROW(d+e, std::exception);
    } else {
        BOOST_ERROR("underflow test only implemented for double so far, need to find examples in float and long double");
    }
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_addition_invalid_result, FPT, test_types){
    // define two FPT numbers suppose to produce a NAN
    FPT a = std::numeric_limits<FPT>::infinity();
    FPT b = -(std::numeric_limits<FPT>::infinity());

    // check adding produced NaN
    BOOST_CHECK(isnan(a+b));

    // construct safe_float version of the same two numbers
    safe_float<FPT> c(a);
    safe_float<FPT> d(b);

    // check the addition throws
    BOOST_CHECK_THROW(c+d, std::exception);
}


BOOST_AUTO_TEST_SUITE_END()


