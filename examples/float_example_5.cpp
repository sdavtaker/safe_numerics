/**
  * This example is based on rule FLP05-C from CERT coding standard.
  * These errors are from unexpected floating-point using denormalized values.
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
    //example for uncatched denormal.
    try {
        float f;
        f = std::numeric_limits<float>::denorm_min();
        assert(std::fpclassify( f ) == FP_SUBNORMAL );
        cout << "no exception was thrown allowing subnormal in float" << endl;
    } catch (std::exception) {
        assert(false); // never arrive here
    }

    //example for catching denormal in safe_float.
    try {
        boost::numeric::safe_float<float> sf;
        sf = std::numeric_limits<float>::denorm_min();
        assert(false); // never arrive here
    } catch (std::exception) {
        cout << "exception was thrown preventing subnormal in safe_float" << endl;
    }

    return 0;
}



