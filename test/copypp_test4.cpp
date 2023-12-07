/* c++
 * @Author: i-curve
 * @Date: 2023-12-02 09:29:13
 * @Last Modified by: i-curve
 * @Name:
 */
#include <iostream>
#include <nlohmann/json.hpp>
#include "icurve/copypp.hh"
#include <gtest/gtest.h>
#include "A.h"
#include "B.h"

using namespace std;

// COPYPP_FIELDS_NON_INTRUSIVE(B, A, id);

TEST(copypp_test4, one) {
    std::string s = R"({"id":5,"name":"i-curve", "age": 25})";
    AA a;
    icurve::copy(a, s);
    EXPECT_TRUE(a.getId() == 5);
    EXPECT_TRUE(a.getName() == "i-curve");
    // EXPECT_TRUE(a.getSex() == true);
    cout << a.getId() << ", " << a.getName() << "," << a.getSex() << endl;
}

TEST(copypp_test, two) {
    std::string s;
    AA a(5, "i-curve", true);
    icurve::copy(s, a);
    EXPECT_TRUE(a.getId() == 5);
    EXPECT_TRUE(a.getName() == "i-curve");
    EXPECT_TRUE(a.getSex() == true);
    cout << a.getId() << ", " << a.getName() << "," << a.getSex() << endl;
}

TEST(copypp_test, three) {
    AA a[3];
    BB b[2] = {BB(1, "first", true), BB(2, "second", false)};
    icurve::copy<AA, 3, BB, 2>(a, b);
    // icurve::copy(std::span<AA>(a, 3), std::span<BB>(b, 2));
    // icurve::copy(std::span<AA>(a), std::span<BB>(b));
    for (int i = 0; i < 2; i++) {
        EXPECT_TRUE(a[i].getId() == b[i].getId());
        EXPECT_TRUE(a[i].getName() == b[i].getName());
        EXPECT_TRUE(a[i].getSex() == b[i].getSex());
    }
    // std::span<AA, 3>(a);
}

TEST(copypp_test, four) {
    vector<AA> a;
    vector<BB> b = {BB(1, "first", true), BB(2, "second", false)};
    icurve::copy(a, b);
    for (int i = 0; i < 2; i++) {
        EXPECT_TRUE(a[i].getId() == b[i].getId());
        EXPECT_TRUE(a[i].getName() == b[i].getName());
        EXPECT_TRUE(a[i].getSex() == b[i].getSex());
    }
}

TEST(copypp_test, five) {
    std::array<AA, 2> a;
    std::array<BB, 3> b = {BB(1, "first", true), BB(2, "second", false)};
    icurve::copy(a, b);
    for (int i = 0; i < 2; i++) {
        EXPECT_TRUE(a[i].getId() == b[i].getId());
        EXPECT_TRUE(a[i].getName() == b[i].getName());
        EXPECT_TRUE(a[i].getSex() == b[i].getSex());
    }
}