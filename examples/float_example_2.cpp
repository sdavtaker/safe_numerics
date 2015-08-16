/**
  * This example is based on rule FLP34-C and FLP36-C from CERT coding standard.
  * These errors are produced by approximation problems when casting.
  */

#include <cmath>
#include <iostream>
#include <cassert>
#include <safe_float.hpp>
#include <safe_math.hpp>
#include <limits>

using namespace std;
int main() {
//    //example for uncatched int to float aproximation
//    try {
//        int i = (2<<(std::numeric_limits<float>::digits+2))+1;
//        float unsafe_var;
//        unsafe_var = i;
//        cout << "no exception was thrown when casting from non representable int using float" << endl;
//    } catch (std::exception) {
//        assert(false); // never arrive here
//    }

//    //example for catching example int to float aproximation
//    try {
//        int i;
//        i = (2<<(std::numeric_limits<float>::digits+2))+1;
//        boost::numeric::safe_float<float> safe_var;
//        safe_var = i;
//        assert(false); // never arrive here
//    } catch (std::exception) {
//        cout << "exception was thrown when casting from non representable int using safe_float" << endl;
//    }

//    //example for uncatched float to int out-of-range representation
//    try {
//        float unsafe_var = std::numeric_limits<float>::max();
//        int i;
//        i = unsafe_var;
//        cout << "no exception was thrown when casting a large value to int using float" << endl;
//    } catch (std::exception) {
//        assert(false); // never arrive here
//    }

//    //example for catching float to int out-of-range representation
//    try {
//        boost::numeric::safe_float<float> safe_var = std::numeric_limits<float>::max();
//        int i;
//        i = safe_var;
//        assert(false); // never arrive here
//    } catch (std::exception) {
//        cout << "exception was thrown when casting a large value to int using safe_float" << endl;
//    }

//    //example for uncatched narrowing
//    try {
//        double unsafe_to_narrow = std::numeric_limits<double>::max();
//        float unsafe_var;
//        unsafe_var = unsafe_to_narrow;
//        cout << "no exception was thrown when narrowing non representable number using float" << endl;
//    } catch (std::exception) {
//        assert(false); // never arrive here
//    }

//    //example for catching narrowing
//    try {
//        double unsafe_to_narrow = std::numeric_limits<double>::max();
//        boost::numeric::safe_float<float> safe_var;
//        safe_var = unsafe_to_narrow;
//        assert(false); // never arrive here
//    } catch (std::exception) {
//        cout << "exception was thrown when narrowing non representable number using safe_float" << endl;
//    }

    return 1;
}


