/* c++
 * @Author: i-curve
 * @Date: 2023-12-18 16:31:11
 * @Last Modified by: i-curve
 * @Name:
 */
#include <iostream>
#include <nlohmann/json.hpp>
#include <list>
#include "icurve/copypp.hh"
#include <gtest/gtest.h>
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
    checkAA(a[0], b[0]);
    checkAA(a[1], b[1]);
    // icurve::copy(std::span<AA>(a, 3), std::span<BB>(b, 2));
    // icurve::copy(std::span<AA>(a), std::span<BB>(b));
}

TEST(COPYPP_ARRAY, _2) {
    std::array<AA, 2> a;
    std::array<BB, 2> b = {BB(1, "first", true), BB(2, "second", false)};
    // a.clear();
    icurve::copy(a, b);
    for (int i = 0; i < 2; i++) {
        EXPECT_TRUE(a[i].getId() == b[i].getId());
        EXPECT_TRUE(a[i].getName() == b[i].getName());
        EXPECT_TRUE(a[i].getSex() == b[i].getSex());
    }
}

TEST(COPYPP_ARRAY, _3) {
    AA a[3];
    BB b[2] = {BB(1, "first", true), BB(2, "second", false)};
    std::span<AA> aa(a);
    std::span<BB> bb(b);
    icurve::copy(aa, bb);
    checkAA(aa[0], bb[0]);
    checkAA(aa[1], bb[1]);
}

TEST(COPYPP_ARRAY, _4) {
    std::vector<AA> a;
    std::vector<BB> b = {BB(1, "first", true), BB(2, "second", false)};
    // std::back_insert_iterator(a);
    // std::vector<AA>::it
    // std::back_inserter(b, BB(1, "first", true));
    icurve::copy(a, b);
    for (int i = 0; i < 2; i++) {
        EXPECT_TRUE(a[i].getId() == b[i].getId());
        EXPECT_TRUE(a[i].getName() == b[i].getName());
        EXPECT_TRUE(a[i].getSex() == b[i].getSex());
    }
}

TEST(COPYPP_ARRAY, _5) {
    std::list<int> n1;
    // std::back_insert(n1, 12);
    n1.push_back(5);
}
TEST(COPYPP_ARRAY, _x) {
    A a = {3, "minal a", false};
    B b;
    /// compile error
    // icurve::copy(b, a);
    int c = 25;
    int d;
    icurve::copy(d, c);
}

TEST(COPYPP_ARRAY, tmp) {
    int a[3] = {1, 2, 3};
    int b[3];
    icurve::copy(b, a);
    EXPECT_TRUE(a[0] == b[0]);
    EXPECT_TRUE(a[1] == b[1]);
    EXPECT_TRUE(a[2] == b[2]);
    int c = 5;
    int d;
    icurve::copy(d, c);
    EXPECT_TRUE(c == d);
}