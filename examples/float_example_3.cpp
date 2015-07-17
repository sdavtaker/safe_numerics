/**
  * This example is based on rule FLP01-C/CPP & FLP02-C/CPP from CERT coding standard.
  * These errors are produced by rearrange of operations give diff result or inexact operations.
  */

#include <cmath>
#include <iostream>
#include <cassert>
#include <safe_float.hpp>
#include <safe_math.hpp>
#include <limits>

using namespace std;
int main() {
    //example for uncatched int to float aproximation
    try {
        float a, b, c, d;
        a = (8 << std::numeric_limits<float>::digits);
        b = -(8 << std::numeric_limits<float>::digits);
        c = 2;
        d = 2;

        c += a;
        c += b;

        a += b;
        d += a;

        assert(d != c);

        cout << "no exception was thrown when rearrange error happened on float" << endl;
    } catch (std::exception) {
        assert(false); // never arrive here
    }

    //example for catching example int to float aproximation
    try {
        boost::numeric::safe_float<float> a, b, c, d;
        a = (8 << std::numeric_limits<float>::digits);
        b = -(8 << std::numeric_limits<float>::digits);
        c = 2;
        d = 2;

        c += a;
        c += b;

        a += b;
        d += a;

        assert(false); // never arrive here
    } catch (std::exception) {
        cout << "exception was thrown preventing rearrange error to happen on safe_float" << endl;
    }

    return 0;
}


