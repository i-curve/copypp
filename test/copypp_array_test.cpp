/* c++
 * @Author: i-curve
 * @Date: 2023-12-18 16:31:11
 * @Last Modified by: i-curve
 * @Name:
 */
#include <iostream>
#include <nlohmann/json.hpp>
#include "icurve/copypp.hh"
#include <gtest/gtest.h>
#include "A.h"
#include "B.h"

TEST(COPYPP_ARRAY, TEXT_KNOW) {
    if (std::is_convertible<int, double>::value) {
        std::cout << "can change int to double\n";
    } else {
        std::cout << "can't change int to double\n";
    }
    if (std::is_convertible<double, int>::value) {
        std::cout << "cant chagne double to int\n";
    } else {
        std::cout << "can't change double to int\n";
    }
}

TEST(COPYPP_ARRAY, _1) {
    AA a[3];
    BB b[2] = {BB(1, "first", true), BB(2, "second", false)};

    icurve::copy(a, b);
    // std::copy();
}

TEST(COPYPP_ARRAY, _2) {
    A a = {3, "minal a", false};
    B b;
    /// compile error
    // icurve::copy(b, a);
    int c = 25;
    int d;
    // icurve::copy(d, c);
}

TEST(COPYPP_ARRAY, tmp) {
    int a[3] = {1, 2, 3};

    int b[3];
    std::copy(a, a + 3, b);
    int c = 5;
    int d;
    // icurve::copy(d, c);
    // std::negation<std::bool_constant<true>>;
}