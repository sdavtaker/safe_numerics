#define BOOST_TEST_MODULE Main
#include <boost/test/included/unit_test.hpp>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/list.hpp>
#include <cmath>

#include <safe_float.hpp>

//types to be tested
using test_types=boost::mpl::list<
    float, double, long double
>;

using namespace boost::numeric;

BOOST_AUTO_TEST_SUITE( safe_float_casting_test_suite )

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_do_not_construct_nans, FPT, test_types){
    BOOST_CHECK_THROW(safe_float<FPT>(NAN), std::exception);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_not_failing_cast_from_int, FPT, test_types){
    if (std::is_same<FPT, long double>::value){
        BOOST_ERROR("need to define the test for long double");
    } else {
        long long int i = 2;
        i <<= (std::numeric_limits<FPT>::digits+2);
        i++;
        BOOST_CHECK_THROW(safe_float<FPT>(i), std::exception);
    }
}


BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_not_failing_cast_to_int, FPT, test_types){
    BOOST_ERROR("feature not implemented");
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_not_narrowing, FPT, test_types){
    if (! std::is_same<FPT, long double>::value){ //long double doesn't narrow (for now)
        long double ld = std::numeric_limits<FPT>::max();
        ld *= 2;
        BOOST_CHECK_THROW(safe_float<FPT>(ld), std::exception);
    }
}


BOOST_AUTO_TEST_SUITE_END()
