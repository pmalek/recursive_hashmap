#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include "HashMap.h"
#include "ArgsNumberOnlyCheck.h"

using namespace std;

/**
 * This method calculates value for the following formula:
 * f(0) = 1
 * f(1) = 1
 * f(2n) = f(n)
 * f(2n+1) = f(n) + f(n-1)
 *
 * Helping itself with hm (which is of HashMap<> type) to store cached values
 */
template<typename T>
T f(T v, HashMap<T, T> &hm)
{
    if (0 == v || 1 == v)
    {
        return 1;
    }

    T value;
    bool exists = hm.get(v, value);
    if (exists)
    {
        // value ( f(v) ) already exists in the hash map, so return it
        return value;
    }

    if (0 == (v % 2))
    {
        T v_over_2 = v / 2;
        exists = hm.get(v_over_2, value);
        if (!exists)
        {
            value = f(v_over_2, hm);
            hm.put(v_over_2, value);
        }
        return value; // f(v / 2);
    }
    else
    {
        T v_over_2 = v / 2;
        exists = hm.get(v_over_2, value);
        if (!exists)
        {
            value = f(v_over_2, hm);
            hm.put(v_over_2, value);
        }

        T value2;
        T v_over_2_minus_1 = v_over_2 - 1;
        exists = hm.get(v_over_2_minus_1, value2);
        if (!exists)
        {
            value2 = f(v_over_2_minus_1, hm);
            hm.put(v_over_2_minus_1, value2);
        }

        return value + value2; // f(v / 2) + f((v / 2) - 1);
    }
};

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Please pass in the program parameter (integer)" << endl;
        return 1;
    }

    if ( !ArgsNumberOnlyCheck::check(argv[1]))
        return 1;

    // HashMap to help speed up the f() method by caching the results
    HashMap<boost::multiprecision::cpp_int, boost::multiprecision::cpp_int> hm;

    boost::multiprecision::cpp_int val(argv[1]);

    cout << "return value: " << f(val, hm) << endl;

    return 0;
}