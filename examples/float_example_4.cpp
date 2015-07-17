/**
  * This example is based on rule FLP04-CPP from CERT coding standard.
  * These errors are from unexpected floating-point inputs for exceptional values
  */

#include <cmath>
#include <iostream>
#include <cassert>
#include <safe_float.hpp>
#include <safe_math.hpp>
#include <limits>
#include <sstream>

using namespace std;
int main() {
    //example for uncatched NaN input in float
    try {
        std::stringstream ss;
        ss.str("NaN");
        float f;
        ss >> f;
        assert(isnan(f));
        cout << "no exception was thrown allowing NaN input in float" << endl;
    } catch (std::exception) {
        assert(false); // never arrive here
    }

    //example for catching NaN input in safe_float.
    try {
        std::stringstream ss;
        ss.str("NaN");
        boost::numeric::safe_float<float> sf;
        ss >> sf;
        assert(false); // never arrive here
    } catch (std::exception) {
        cout << "exception was thrown preventing NaN input in safe_float" << endl;
    }

    //example for uncatched inf input in float
    try {
        std::stringstream ss;
        ss.str("inf");
        float f;
        ss >> f;
        assert(isinf(f));
        cout << "no exception was thrown allowing inf input in float" << endl;
    } catch (std::exception) {
        assert(false); // never arrive here
    }

    //example for catching inf input in safe_float.
    try {
        std::stringstream ss;
        ss.str("inf");
        boost::numeric::safe_float<float> sf;
        ss >> sf;
        assert(false); // never arrive here
    } catch (std::exception) {
        cout << "exception was thrown preventing inf input in safe_float" << endl;
    }

    return 0;
}



