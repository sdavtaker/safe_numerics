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

BOOST_AUTO_TEST_SUITE( safe_float_compare_test_suite )

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_equality_checks, FPT, test_types){
    safe_float<FPT> a(17.0);
    safe_float<FPT> b(17.0);
    safe_float<FPT> c(23.0);
    safe_float<FPT> d(std::numeric_limits<FPT>::infinity());
    BOOST_CHECK(a == b);
    BOOST_CHECK( ! (a == c) );
    BOOST_CHECK( d == d);
    BOOST_CHECK( ! (d == a) );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_non_equality_checks, FPT, test_types){
    safe_float<FPT> a(17.0);
    safe_float<FPT> b(17.0);
    safe_float<FPT> c(23.0);
    safe_float<FPT> d(std::numeric_limits<FPT>::infinity());
    BOOST_CHECK(! (a != b));
    BOOST_CHECK( a != c );
    BOOST_CHECK(! (d != d));
    BOOST_CHECK( d != a );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_lt_checks, FPT, test_types){
    safe_float<FPT> a(17.0);
    safe_float<FPT> b(23.0);
    safe_float<FPT> c(37.0);
    safe_float<FPT> d(std::numeric_limits<FPT>::infinity());
    BOOST_CHECK( a < b);
    BOOST_CHECK( b < c );
    BOOST_CHECK(! (a < a));
    BOOST_CHECK(! (c < a));
    BOOST_CHECK(! (d < d));
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_other_compares_implemented, FPT, test_types){
    safe_float<FPT> a(17.0);
    safe_float<FPT> b(23.0);
    BOOST_CHECK( b > a);
    BOOST_CHECK( b >= b );
    BOOST_CHECK( a <= a );
}

BOOST_AUTO_TEST_SUITE_END()
