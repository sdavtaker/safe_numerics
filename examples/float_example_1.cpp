/**
  * This example is based on rule FLP32-C from CERT coding standard.
  * Three errors may occur when oeprating with math.h functions: domain, Pole, or range errors.
  */

#include <cmath>
#include <iostream>
#include <cassert>
#include <safe_float.hpp>
#include <safe_math.hpp>

using namespace std;
int main() {
    //example for uncatched domain error
    try {
        float unsafe_var = 2.0;
        float unsafe_result;
        unsafe_result = atanh(unsafe_var);
        cout << "no exception was thrown for atanh(2) when using float" << endl;
    } catch (std::exception) {
        assert(false); // never arrive here
    }

    //example for catching the domain error by safe_float
    try {
        boost::numeric::safe_float<float> safe_var = 2.0;
        boost::numeric::safe_float<float> safe_result;
        safe_result = std::atanh(safe_var);
        assert(false); // never arrive here
    } catch (std::exception) {
        cout << "exception was thrown for acos(2) when using safe_float" << endl;
    }

    //example for uncatched pole error
    try {
        float unsafe_var = 1.0;
        float unsafe_result;
        unsafe_result = atanh(unsafe_var);
        cout << "no exception was thrown for atanh(1) when using float" << endl;
    } catch (std::exception) {
        assert(false); // never arrive here
    }

    //example for catching the pole error by safe_float
    try {
        boost::numeric::safe_float<float> safe_var = 1.0;
        boost::numeric::safe_float<float> safe_result;
        safe_result = std::atanh(safe_var);
        assert(false); // never arrive here
    } catch (std::exception) {
        cout << "exception was thrown for atanh(1) when using safe_float" << endl;
    }


    //example for uncatched range error
    try {
        float unsafe_var = nexttowardf(1, -INFINITY);
        float unsafe_result;
        unsafe_result = atanh(unsafe_var);
        cout << "no exception was thrown for atanh(1) when using float" << endl;
    } catch (std::exception) {
        assert(false); // never arrive here
    }

    //example for catching the pole error by safe_float
    try {
        boost::numeric::safe_float<float> safe_var = nexttowardf(1, -INFINITY);
        boost::numeric::safe_float<float> safe_result;
        safe_result = std::atanh(safe_var);
        assert(false); // never arrive here
    } catch (std::exception) {
        cout << "exception was thrown for atanh(1) when using safe_float" << endl;
    }

    return 0;
}


