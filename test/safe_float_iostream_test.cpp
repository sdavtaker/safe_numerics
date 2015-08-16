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

BOOST_AUTO_TEST_SUITE( safe_float_iostream_test_suite )

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_ostream_outs_same_than_type, FPT, test_types){
    FPT a(17.0);
    FPT b(std::numeric_limits<FPT>::infinity());
    FPT c(std::numeric_limits<FPT>::max());
    FPT d(std::numeric_limits<FPT>::min());
    FPT e(std::numeric_limits<FPT>::lowest());

    safe_float<FPT> sa(a);
    safe_float<FPT> sb(b);
    safe_float<FPT> sc(c);
    safe_float<FPT> sd(d);
    safe_float<FPT> se(e);

    std::stringstream ss_native;
    std::stringstream ss_safe;

    ss_native << a;
    ss_safe << sa;
    BOOST_CHECK_EQUAL(ss_native.str(), ss_safe.str());
    ss_native.str("");
    ss_safe.str("");

    ss_native << b;
    ss_safe << sb;
    BOOST_CHECK_EQUAL(ss_native.str(), ss_safe.str());
    ss_native.str("");
    ss_safe.str("");

    ss_native << c;
    ss_safe << sc;
    BOOST_CHECK_EQUAL(ss_native.str(), ss_safe.str());
    ss_native.str("");
    ss_safe.str("");

    ss_native << d;
    ss_safe << sd;
    BOOST_CHECK_EQUAL(ss_native.str(), ss_safe.str());
    ss_native.str("");
    ss_safe.str("");

    ss_native << e;
    ss_safe << se;
    BOOST_CHECK_EQUAL(ss_native.str(), ss_safe.str());
    ss_native.str("");
    ss_safe.str("");

}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_istream_safe_input_is_read, FPT, test_types){
    std::stringstream ss;
    ss.str("1.5");
    safe_float<FPT> sf;
    ss >>sf;
    safe_float<FPT> sr(1.5);
    BOOST_CHECK_EQUAL(sf, sr);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( safe_float_istream_detects_wrong_input, FPT, test_types){
    std::stringstream ss;
    safe_float<FPT, 0> sf;
    ss.str("nan");
    BOOST_CHECK_THROW(ss >> sf, std::exception);

    ss.str("inf");
    BOOST_CHECK_THROW(ss >> sf, std::exception)


}

BOOST_AUTO_TEST_SUITE_END()



