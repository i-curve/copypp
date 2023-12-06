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