/* c++
 * @Author: i-curve
 * @Date: 2023-12-19 13:08:14
 * @Last Modified by: i-curve
 * @Name:
 */
#include <iostream>
#include <nlohmann/json.hpp>
#include <fmt/core.h>
#include <list>
#include <gtest/gtest.h>
#include "icurve/copypp.hh"
#include "B.h"

TEST(COPYPP_STL, _1) {
    std::vector<AA> a = {AA(1, "first", true), AA(2, "second", false)};
    std::list<BB> b;
    icurve::copy(b, a);
    EXPECT_TRUE(b.size() == a.size());
    size_t s = 0;
    for (auto [ap, bp] = std::make_tuple(a.begin(), b.begin());
         ap != a.end(), bp != b.end(); ++ap, ++bp) {
        s++;
        checkAA(*ap, *bp);
    }
    EXPECT_TRUE(s == a.size());
}

TEST(COPYPP_STL, _2) {
    std::vector<AA> a = {AA(1, "first", true), AA(2, "second", false)};
    std::array<BB, 1> b;
    std::array<BB, 3> c;
    icurve::copy(b, a);
    icurve::copy(c, a);
    EXPECT_TRUE(a.size() == 2);
    EXPECT_TRUE(b.size() == 1);
    checkAA(a[0], b[0]);
    checkAA(a[0], c[0]);
    checkAA(a[1], c[1]);
}